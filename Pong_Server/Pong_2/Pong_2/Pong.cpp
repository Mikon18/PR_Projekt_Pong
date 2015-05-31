#include "Pong.h"

struct users
{
	int X;
	int Y;
};
struct users users_paddles[4];
bool isCorrect(int buf[])
{
	if (buf[0] < 0 || buf[0] > 3)
	{
		return false;
	}
	switch (buf[0])
	{
		case 0:
			if (buf[1] > SCREEN_WIDTH - 30 || buf[1] < 30)
			{
				return false;
			}
			break;
		case 1:
			if (buf[1] > SCREEN_WIDTH - 30 || buf[1] < 30)
			{
				return false;
			}
			break;
		case 2:
			if (buf[1] > SCREEN_HEIGHT - 30 || buf[1] < 30)
			{
				return false;
			}
			break;
		case 3:
			if (buf[1] > SCREEN_HEIGHT - 30 || buf[1] < 30)
			{
				return false;
			}
			break;
		}
	return true;
}
Pong::Pong()
{
}
void Pong::randomEvent(int lastEvent)
{
	srand(time(NULL));
	int i = rand() % 4 + 1;
	while (lastEvent == i)
	{
		i = rand() % 4 + 1;
	}
	switch (i)
	{
	case 1:
		speed.setPosition(rand() % (SCREEN_WIDTH - 200) + 100, rand() % (SCREEN_HEIGHT - 200) + 100);
		break;
	case 2:
		slow.setPosition(rand() % (SCREEN_WIDTH - 200) + 100, rand() % (SCREEN_HEIGHT - 200) + 100);
		break;
	case 3:
		reverse.setPosition(rand() % (SCREEN_WIDTH - 200) + 100, rand() % (SCREEN_HEIGHT - 200) + 100);
		break;
	}
}
void Pong::run()
{
	/*SDL*/
	users_paddles[0].X = (SCREEN_WIDTH / 2) - 150 / 2;
	users_paddles[0].Y = SCREEN_HEIGHT - 30;
	users_paddles[1].X = (SCREEN_WIDTH / 2) - 150 / 2;
	users_paddles[1].Y = 0;
	users_paddles[2].X = 0;
	users_paddles[2].Y = (SCREEN_HEIGHT / 2) - 150 / 2;
	users_paddles[3].X = SCREEN_WIDTH - 30;
	users_paddles[3].Y = (SCREEN_HEIGHT / 2) - 150 / 2;
	ball.setPosition((SCREEN_WIDTH / 2) - 12, (SCREEN_HEIGHT / 2) - 12);
	paddles[0].setPosition((SCREEN_WIDTH / 2) - 150 / 2, SCREEN_HEIGHT - 30);
	paddles[1].setPosition((SCREEN_WIDTH / 2) - 150 / 2, 0);
	paddles[2].setPosition(0, (SCREEN_HEIGHT / 2) - 150 / 2);
	paddles[3].setPosition(SCREEN_WIDTH - 30, (SCREEN_HEIGHT / 2) - 150 / 2);
	paddles[0].setSize(150, 30);
	paddles[1].setSize(150, 30);
	paddles[2].setSize(30, 150);
	paddles[3].setSize(30, 150);
	speed.inactive = true;
	slow.inactive = true;
	reverse.inactive = true;
	int tmp;
	/*Sockety*/
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	int buf[BUFLEN];
	WSADATA wsa;
	slen = sizeof(si_other);
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	int user_count = 0;
	clock_t eventTime = clock();
	clock_t startTime = clock();
	///////////////////////////////////////////////////
	while (1)
	{
		if ((recv_len = recvfrom(s, (char*)buf, BUFLEN*sizeof(int), 0, (struct sockaddr *) &si_other, &slen)) != SOCKET_ERROR)
		{
			if (buf[0] == -1)
			{
				buf[0] = user_count++;
				if (sendto(s, (char*)buf, BUFLEN*sizeof(int), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
				{
				}
				if (user_count == MAX_USERS)
				{
					startTime = clock();
					eventTime = clock();
				}
			}
			else
			{
				if (isCorrect(buf))
				{
					if (buf[0] <= 1)
					{
						paddles[buf[0]].posX = buf[1];
						users_paddles[buf[0]].X = buf[1];
					}
					else
					{
						paddles[buf[0]].posY = buf[1];
						users_paddles[buf[0]].Y = buf[1];
					}
				}
				buf[0] = users_paddles[0].X;
				buf[1] = users_paddles[1].X;
				buf[2] = users_paddles[2].Y;
				buf[3] = users_paddles[3].Y;
				if (user_count > MAX_USERS)
				{
					buf[4] = ball.posX;
					buf[5] = ball.posY;
				}
				else
				{
					buf[4] = -200;
					buf[5] = -200;
				}
				tmp = clock();
				if (speed.inactive == true && slow.inactive == true && reverse.inactive == true && ((tmp-eventTime)>10000) &&
					user_count > MAX_USERS)
				{
					eventTime = clock();
					randomEvent(ball.lastEvent);
				}
				if (speed.inactive == false)
				{
					buf[6] = 1;
					buf[7] = speed.posX;
					buf[8] = speed.posY;
				}
				if (slow.inactive == false)
				{
					buf[6] = 3;
					buf[7] = slow.posX;
					buf[8] = slow.posY;
				}
				if (reverse.inactive == false)
				{
					buf[6] = 2;
					buf[7] = reverse.posX;
					buf[8] = reverse.posY;
				}
				if (sendto(s, (char*)buf, BUFLEN * sizeof(int), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
				{
				}

			}
			tmp = clock();
			if ((tmp - startTime) > 4000 && user_count == MAX_USERS)
			{
				user_count++;
			}
			if (user_count > MAX_USERS)
			{
				ball.move(paddles, &speed, &reverse, &slow, &eventTime);
			}
		}
	}
	closesocket(s);
	WSACleanup();
}