// 6522060 zy22060 Youqi RONG

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

struct nofly_list {
	int x;
	int y;
	int r;
	struct nofly_list *next;
};
typedef struct nofly_list NList;

struct flightplan_list {
	int a;
	int b;
	struct flightplan_list *next;
};
typedef struct flightplan_list FList;

struct crosspoint_list {
	float cx;
	int Cx;
	int Cy;
	struct crosspoint_list *next;
};
typedef struct crosspoint_list CList;

int noflycheck(NList **nofly)
{
	FILE *fp1;
	fp1 = fopen("nofly.txt", "r");
	if(fp1 == NULL)
	{
		perror("Cannot open no-fly zone file.");
		exit(1);
	}
	else
	{
		int x, y, r;
		int i = 0;
		if(feof(fp1))
		{
			return 0;
		}
		while(!feof(fp1))
		{
			char m = getc(fp1);
			if(feof(fp1))
			{
				break;
			}
			else if(m == 10)
			{
				// goto the next line
				while(1)
				{
					m = getc(fp1);
					if(m == 10)
					{
						continue;
					}
					else
					{
						break;
					}
				}
			}
			else if(m == 35)
			{
				while(1)
				{
					m = getc(fp1);
					if(m == 10)
					{
						break;
					}
					else
					{
						continue;
					}
				}
			}
			else if(m < 48 || m > 57)
			{
				printf("No-fly zone file invalid.\n"); 
				exit(2);
			}
			else
			{
				fseek(fp1, -1, SEEK_CUR); // go backward one character
				fscanf(fp1, "%d", &x);
				if(x >= 0 && x<10000)
				{
					while(1)
					{
						char a = getc(fp1);
						if(a == 32)
						{
							continue;
						}
						else if(a >= 48 && a <=57)
						{
							fseek(fp1, -1, SEEK_CUR);
							break;
						}
						else
						{
							printf("No-fly zone file invalid.\n");
							exit(2);
						}
					}
					fscanf(fp1, "%d", &y);
					if(y >= 0 && y < 10000)
					{
						while(1)
						{
							char b = getc(fp1);
							if(b == 32)
							{
								continue;
							}
							else if(b >= 48 && b <=57)
							{
								fseek(fp1, -1, SEEK_CUR);
								break;
							}
							else
							{
								printf("No-fly zone file invalid.\n");
								exit(2);
							}
						}
						fscanf(fp1, "%d", &r);
						if(r > 0 && r < 10000)
						{
							char c = getc(fp1);
							if(c != 10)
							{
								printf("No-fly zone file invalid.\n");
								exit(2);
							}
							else
							{
								if(*nofly == NULL)
								{
									NList *n = malloc(sizeof(NList));
									if(n == NULL)
									{
										// error, cannot allocate memory for new list node
										printf("Unable to allocate memory.\n");
										exit(5);
									}
									else
									{
										n->x = x;
										n->y = y;
										n->r = r;
										n->next = NULL;
										*nofly = n;
									}
									
								}
								else
								{
									NList *cur = *nofly;
									while(cur->next != NULL)
									{
										cur = cur->next;
									}
									NList *n = malloc(sizeof(NList));
									if(n == NULL)
									{
										// error, cannot allocate memory for new list node
										printf("Unable to allocate memory.\n");
										exit(5);
									}
									else
									{
										n->x = x;
										n->y = y;
										n->r = r;
										n->next = NULL;
										cur->next = n;
									}
								}
								i++;
							}
						}
						else
						{
							printf("No-fly zone file invalid.\n");
							exit(2);
						}
					}
					else
					{
						printf("No-fly zone file invalid.\n");
						exit(2);
					}
				}
				else
				{
					printf("No-fly zone file invalid.\n");
					exit(2);
				}
			}
		}
		return i;
	}
	fclose(fp1);
}

int flightplancheck(FList **flightplan)
{
	FILE *fp2;
	fp2 = fopen("flightplan.txt", "r");
	if(fp2 == NULL)
	{
		perror("Cannot open flight plan file.");
		exit(1);
	}
	else
	{
		int a, b;
		int i = 0;
		while(!feof(fp2))
		{
			char m = getc(fp2);
			if(feof(fp2))
			{
				break;
			}
			else if(m == 10)
			{
				// goto the next line
				while(1)
				{
					m = getc(fp2);
					if(m == 10)
					{
						continue;
					}
					else
					{
						break;
					}
				}
			}
			else if(m == 35)
			{
				while(1)
				{
					m = getc(fp2);
					if(m == 10)
					{
						break;
					}
					else
					{
						continue;
					}
				}
			}
			else if(m < 48 || m > 57)
			{
				printf("Flight plan file invalid.\n");
				exit(3);
			}
			else
			{
				fseek(fp2, -1, SEEK_CUR); // go backward one character
				fscanf(fp2, "%d", &a);
				if(a >= 0 && a < 10000)
				{
					while(1)
					{
						char n = getc(fp2);
						if(n == 32)
						{
							continue;
						}
						else if(n >= 48 && n <=57)
						{
							fseek(fp2, -1, SEEK_CUR);
							break;
						}
						else
						{
							printf("Flight plan file invalid.\n");
							exit(3);
						}
					}
					fscanf(fp2, "%d", &b);
					if(b >= 0 && b < 10000)
					{
						char k = getc(fp2);
						if(k != 10)
						{
							printf("Flight plan file invalid.\n");
							exit(3);
						}
						else
						{
							if(*flightplan == NULL)
								{
									FList *n = malloc(sizeof(NList));
									if(n == NULL)
									{
										// error, cannot allocate memory for new list node
										printf("Unable to allocate memory.\n");
										exit(5);
									}
									else
									{
										n->a = a;
										n->b = b;
										n->next = NULL;
										*flightplan = n;
									}
								}
								else
								{
									FList *cur = *flightplan;
									while(cur->next != NULL)
									{
										cur = cur->next;
									}
									FList *n = malloc(sizeof(NList));
									if(n == NULL)
									{
										// error, cannot allocate memory for new list node
										printf("Unable to allocate memory.\n");
										exit(5);
									}
									else
									{
										if(cur->a == a && cur->b == b)
										{
											printf("Flight plan file invalid.\n");
											exit(3);
										}
										else
										{
											n->a = a;
											n->b = b;
											n->next = NULL;
											cur->next = n;
										}
									}
								}
							i++;
						}
					}
					else
					{
						printf("Flight plan file invalid.\n");
						exit(3);
					}
				}
				else
				{
					printf("Flight plan file invalid.\n");
					exit(3);
				}
			}
		}
		if(i < 2)
		{
			printf("Flight plan file invalid.\n");
			exit(3);
		}
		else
		{
			return i;
		}
	}
	fclose(fp2);
}

// function learnt from lab 8 list_get
int list_get1x(NList *start, int i)
{
	NList *cur = start;
	if(i <= 0)
	{
		printf("Invalid index!\n");
		exit(6);
	}
	else
	{
		while(cur != NULL)
		{
			if(i == 1)
			{
				return cur->x;
			}
			else
			{
				i--;
				cur = cur->next;
			}
		}
		return -1;
	}
}

// function learnt from lab 8 list_get
int list_get1y(NList *start, int i)
{
	NList *cur = start;
	if(i <= 0)
	{
		printf("Invalid index!\n");
		exit(6);
	}
	else
	{
		while(cur != NULL)
		{
			if(i == 1)
			{
				return cur->y;
			}
			else
			{
				i--;
				cur = cur->next;
			}
		}
		return -1;
	}
}

// function learnt from lab 8 list_get
int list_get1r(NList *start, int i)
{
	NList *cur = start;
	if(i <= 0)
	{
		printf("Invalid index!\n");
		exit(6);
	}
	else
	{
		while(cur != NULL)
		{
			if(i == 1)
			{
				return cur->r;
			}
			else
			{
				i--;
				cur = cur->next;
			}
		}
		return -1;
	}
}

// function learnt from lab 8 list_get
int list_get2x(FList *start, int j)
{
	FList *cur = start;
	if(j <= 0)
	{
		printf("Invalid index!\n");
		exit(6);
	}
	else
	{
		while(cur != NULL)
		{
			if(j == 1)
			{
				return cur->a;
			}
			else
			{
				j--;
				cur = cur->next;
			}
		}
		return -1;
	}
}

// function learnt from lab 8 list_get
int list_get2y(FList *start, int j)
{
	FList *cur = start;
	if(j <= 0)
	{
		printf("Invalid index!\n");
		exit(6);
	}
	else
	{
		while(cur != NULL)
		{
			if(j == 1)
			{
				return cur->b;
			}
			else
			{
				j--;
				cur = cur->next;
			}
		}
		return -1;
	}
}

int discrim(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int r)
{
	long int X = pow(Ax, 2) - (2 * Ax * Bx) + pow(Bx, 2) + pow(Ay, 2) - (2 * Ay * By) + pow(By, 2);
	long int Y = (2 * Cx * Bx) - (2 * Cx * Ax) - (2 * Cy * Ay) + (2 * Cy * By) + (2 * Ax * Bx) + (2 * Ay * By) - (2 * pow(Bx, 2)) - (2 * pow(By, 2));
	long int Z = pow(Cx, 2) - (2 * Cx * Bx) + pow(Cy, 2) - (2 * Cy * By) - pow(r, 2) + pow(Bx, 2) + pow(By, 2);

	long int Discrim = pow(Y, 2) - (4 * X * Z);

	if(Discrim < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void cross(CList **crosspoint, int Ax, int Ay, int Bx, int By, int Cx, int Cy, int r)
{
	float x1, y1;
	float x2, y2;

	float k = (float)(Ay - By) / (float)(Ax - Bx);

	float A = pow(k, 2) + 1;

	float B = 2 * k * (Ay - Cy) - 2 * Cx - 2 * pow(k, 2) * Ax;

	float C = pow(Cx, 2) + pow(k, 2) * pow(Ax, 2) - 2 * k * Ax *(Ay - Cy) + pow(Ay - Cy, 2) - pow(r, 2);

	float CDiscrim = pow(B, 2) - (4 * A * C);

	if(CDiscrim >= 0)
	{
		x1 = (-B + sqrt(CDiscrim)) / (2 * A);
		y1 = (k * (x1 - Ax)) + Ay;

		if(x1 >= Ax && x1 <= Bx)
		{
			x1 = pow((x1 - Ax), 2) + pow((y1 - Ay), 2);

			if(*crosspoint == NULL)
			{
				CList *n = malloc(sizeof(CList));
				if(n == NULL)
				{
					// error, cannot allocate memory for new list node
					printf("Unable to allocate memory.\n");
					exit(5);
				}
				else
				{
					n->cx = x1;
					n->Cx = Cx;
					n->Cy = Cy;
					n->next = NULL;
					*crosspoint = n;
				}
									
			}
			else
			{
				CList *cur = *crosspoint;
				while(cur->next != NULL)
				{
					cur = cur->next;
				}
				CList *n = malloc(sizeof(CList));
				if(n == NULL)
				{
					// error, cannot allocate memory for new list node
					printf("Unable to allocate memory.\n");
					exit(5);
				}
				else
				{
					n->cx = x1;
					n->Cx = Cx;
					n->Cy = Cy;
					n->next = NULL;
					cur->next = n;
				}
			}
		}
		else if(x1 >= Bx && x1 <= Ax)
		{
			x1 = pow((x1 - Ax), 2) + pow((y1 - Ay), 2);

			if(*crosspoint == NULL)
			{
				CList *n = malloc(sizeof(CList));
				if(n == NULL)
				{
					// error, cannot allocate memory for new list node
					printf("Unable to allocate memory.\n");
					exit(5);
				}
				else
				{
					n->cx = x1;
					n->Cx = Cx;
					n->Cy = Cy;
					n->next = NULL;
					*crosspoint = n;
				}
									
			}
			else
			{
				CList *cur = *crosspoint;
				while(cur->next != NULL)
				{
					cur = cur->next;
				}
				CList *n = malloc(sizeof(CList));
				if(n == NULL)
				{
					// error, cannot allocate memory for new list node
					printf("Unable to allocate memory.\n");
					exit(5);
				}
				else
				{
					n->cx = x1;
					n->Cx = Cx;
					n->Cy = Cy;
					n->next = NULL;
					cur->next = n;
				}
			}
		}

		x2 = (-B - sqrt(CDiscrim)) / (2 * A);
		y2 = (k * (x2 - Ax)) + Ay;

		if(x2 >= Ax && x2 <= Bx)
		{
			x2 = pow((x2 - Ax), 2) + pow((y2 - Ay), 2);

			if(*crosspoint == NULL)
			{
				CList *n = malloc(sizeof(CList));
				if(n == NULL)
				{
					// error, cannot allocate memory for new list node
					printf("Unable to allocate memory.\n");
					exit(5);
				}
				else
				{
					n->cx = x2;
					n->Cx = Cx;
					n->Cy = Cy;
					n->next = NULL;
					*crosspoint = n;
				}
									
			}
			else
			{
				CList *cur = *crosspoint;
				while(cur->next != NULL)
				{
					cur = cur->next;
				}
				CList *n = malloc(sizeof(CList));
				if(n == NULL)
				{
					// error, cannot allocate memory for new list node
					printf("Unable to allocate memory.\n");
					exit(5);
				}
				else
				{
					n->cx = x2;
					n->Cx = Cx;
					n->Cy = Cy;
					n->next = NULL;
					cur->next = n;
				}
			}
		}
		else if(x2 >= Bx && x2 <= Ax)
		{
			x2 = pow((x2 - Ax), 2) + pow((y2 - Ay), 2);

			if(*crosspoint == NULL)
			{
				CList *n = malloc(sizeof(CList));
				if(n == NULL)
				{
					// error, cannot allocate memory for new list node
					printf("Unable to allocate memory.\n");
					exit(5);
				}
				else
				{
					n->cx = x2;
					n->Cx = Cx;
					n->Cy = Cy;
					n->next = NULL;
					*crosspoint = n;
				}					
			}
			else
			{
				CList *cur = *crosspoint;
				while(cur->next != NULL)
				{
					cur = cur->next;
				}
				CList *n = malloc(sizeof(CList));
				if(n == NULL)
				{
					// error, cannot allocate memory for new list node
					printf("Unable to allocate memory.\n");
					exit(5);
				}
				else
				{
					n->cx = x2;
					n->Cx = Cx;
					n->Cy = Cy;
					n->next = NULL;
					cur->next = n;
				}
			}
		}
	}
}

int root(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int r)
{
	long int X = pow(Ax, 2) - (2 * Ax * Bx) + pow(Bx, 2) + pow(Ay, 2) - (2 * Ay * By) + pow(By, 2);
	long int Y = (2 * Cx * Bx) - (2 * Cx * Ax) - (2 * Cy * Ay) + (2 * Cy * By) + (2 * Ax * Bx) + (2 * Ay * By) - (2 * pow(Bx, 2)) - (2 * pow(By, 2));
	long int Z = pow(Cx, 2) - (2 * Cx * Bx) + pow(Cy, 2) - (2 * Cy * By) - pow(r, 2) + pow(Bx, 2) + pow(By, 2);

	long int Discrim = pow(Y, 2) - (4 * X * Z);

	float d = sqrt(Discrim);

	float t1 = (float)(-Y + d) / (float)(2 * X);

	float t2 = (float)(-Y - d) / (float)(2 * X);


	if(t1 >= 0 && t1 <= 1)
	{
		return 0;
	}
	else if(t2 >= 0 && t2 <= 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

// function learnt from lab 8 list_free
void list_free1(NList **start)
{
   NList *cur = *start;
   while(cur != NULL)
   {
      NList *temp = cur->next;
      free(cur);
      cur = temp;
   }
   *start = NULL;
}

// function learnt from lab 8 list_free
void list_free2(FList **start)
{
   FList *cur = *start;
   while(cur != NULL)
   {
      FList *temp = cur->next;
      free(cur);
      cur = temp;
   }
   *start = NULL;
}

// function learnt from lab 8 list_length
int list_length(CList *start)
{

	if(start == NULL)
	{
		return 0;
	}
	else
	{
		int total = 1;
		CList *cur = start;
		while(cur->next != NULL)
		{
			cur = cur->next;
			total++;
		}
		return total;
	}
}

int main(int argc, char *argv[])
{
	if(argc == 3)
	{
		NList *nofly = NULL;
		int m = noflycheck(&nofly);

		FList *flightplan = NULL;
		int n = flightplancheck(&flightplan);
		
		if(m == 0)
		{
			printf("Flight plan valid.\n");
		}
		else
		{
			for(int i = 1; i <= m; i++)
			{
				int Cx = list_get1x(nofly, i);
				int Cy = list_get1y(nofly, i);
				int r = list_get1r(nofly, i);

				for(int j = 1; j <= n; j++)
				{
					int a = list_get2x(flightplan, j);
					int b = list_get2y(flightplan, j);

					if((pow(Cx - a, 2) + pow(Cy - b, 2)) <= pow(r, 2))
					{
						printf("Invalid flight plan.\n");
						printf("Enters restricted area around %d, %d.\n", Cx, Cy);
						exit(4);
					}
				}
			}
			// check waypoint on or within the circle

			// check segment cross the circle
			CList *crosspoint = NULL;
			for(int j = 1; j <= n - 1; j++)
			{
			
				int Ax = list_get2x(flightplan, j);
				int Ay = list_get2y(flightplan, j);
				int Bx = list_get2x(flightplan, j + 1);
				int By = list_get2y(flightplan, j + 1);

				for(int i = 1; i <= m; i++)
				{
					int Cx = list_get1x(nofly, i);
					int Cy = list_get1y(nofly, i);
					int r = list_get1r(nofly, i);

					int check2 = discrim(Ax, Ay, Bx, By, Cx, Cy, r);

					if(check2 == 0)
					{
						int check3 = root(Ax, Ay, Bx, By, Cx, Cy, r);

						if(check3 == 0)
						{
							cross(&crosspoint, Ax, Ay, Bx, By, Cx, Cy, r);
							
						}
					}
				}
				int crosscount = list_length(crosspoint);

				if(crosscount != 0)
				{
					float minimum = 100000000000000000;
					int CCx = -1;
					int CCy = -1;

					CList *cur = crosspoint;

					for(int i = 0; i < crosscount; i++)
					{
						if(cur->cx < minimum)
						{
							minimum = cur->cx;
							CCx = cur->Cx;
							CCy = cur->Cy;
						}
						cur = cur->next;
					}
					printf("Invalid flight plan.\n");
					printf("Enters restricted area around %d, %d.\n", CCx, CCy);
					exit(4);
				}
			}
			printf("Flight plan valid.\n");
		}
		list_free1(&nofly);
		list_free2(&flightplan);
	}
	else
	{
		printf("Invalid command line arguments. Usage: <noflyzones> <flightplan>\n");
	}
}