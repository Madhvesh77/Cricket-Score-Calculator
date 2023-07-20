#include <stdio.h>
#include <stdlib.h>

//function prototypes
void startnewmatch();
void CalculateScore();
void SetDefaultScores();
void ViewScoreCard();
float Balls_to_Overs(int balls);
void SwitchPlayer();

int score=0,totalovers=0,ballsbowled=0,ballruns=0,strikebatsman=0,nonstrikebatsman=0,bowlid=0;  //global

struct batter 
{
    char name[10];
	int id;
	int runs;
	int ballsfaced;
	float strikerate; 
	int strikeflag;
	int outstatus;
}bat[11];

struct bowler
{
    char name[10];
    int id;
    int ballsbowled;
	int wickets;
	int runsgiven; 
	float economy; 
	int bowlingflag;
}bowl[11];


//Main function
int main()
{
	int choice;
	printf("\n\n\n\n\t\t\t\tWelcome to Cricket scorecard calculator.\n\t\t\t\t");
	printf("1 - Create a new match.\n\t\t\t\t");
	printf("2 - Exit\n\n\t\t\t\t");
	printf("Enter the choice - ");
	scanf("%d", &choice);
	if(choice==1)
		startnewmatch();
	else if(choice==2)
	{
		printf("\n\t\t\t\tQUITTING....");
		return 0;	
	}
	else
	{
		printf("\n\t\t\t\tInvalid choice.\nQUITTING.....");
		return 0;
	}
}

void startnewmatch()
{
    SetDefaultScores();
    system("cls");
    printf("\n\n\n\tPLAYER DETAILS\n\n");
    printf("\tEnter BATTING team players names(11 players):\n");
    int playerindex;
    for(playerindex=1;playerindex<=11;playerindex++)
    {
        printf("\tBatsman %d: ",playerindex);
        bat[playerindex].id=playerindex;
        scanf("%s",&bat[playerindex].name);
    }
    system("cls");
    printf("\n\n\n\tPLAYER DETAILS\n\n");
    printf("\tEnter BOWLING team players names(11 players):\n");
    int j;
    for(j=1;j<=11;j++)
    {
        printf("\tBowler %d: ",j);
        bowl[j].id=j;
        scanf("%s",&bowl[j].name);
    }
    system("cls");
    printf("\n\n\n\n\n\tENTER NUMBER OF OVERS: ");
    scanf("%d",&totalovers);
    CalculateScore();

}

void CalculateScore()
{
	
    int batter1,batter2;
	int nb,bowlid;
    char ballrun='0';
    int started=0;


    while(ballsbowled<=totalovers*6)
    {
    	if(ballsbowled%6==0 && ballsbowled<totalovers*6 )
    	{
    		if(ballsbowled==0 && started==0)
	        {
	        	started=1;
	            system("cls");
	            printf("\n\n\n\t\t SELECT BATSMAN\n\n");
	            printf("\tID  Name      Runs    Balls  Strike Rate\n");
	            int playerindex;
	            for( playerindex = 1; playerindex<=11;playerindex++)
	            {
	                printf("\t%-3d %-10s: %-3d     %-3d    %.2f\n",bat[playerindex].id,bat[playerindex].name,bat[playerindex].runs,bat[playerindex].ballsfaced, bat[playerindex].strikerate);
	            }
	            repeatfirstbatid:
	            printf("\n\tEnter FIRST Batsman ID (1-11): ");
	            scanf("%d",&batter1);
	            if(batter1<1 || batter1>11)
	            {
	                printf("\n\tError:Invalid choice.");
	                goto repeatfirstbatid;
	            }else 
	            {
	                strikebatsman=batter1;
	                bat[batter1].strikeflag=1;
	            }
	            repeatsecondbatid:
	            printf("\tEnter SECOND Batsman ID (1-11): ");
	            scanf("%d",&batter2);
	            if(bat[batter2].strikeflag)
	                {
	                    printf("\tBatsman %d:%s is already batting.\n\tENTER AGAIN\n",bat[batter2].id,bat[batter2].name);
	                    goto repeatsecondbatid;
	                }
	            if(batter2<1 || batter2>11)
	            { 
	                printf("\n\tError:Invalid choice.");
	                goto repeatsecondbatid;
	            }else 
	            {
	                nonstrikebatsman=batter2;
	                bat[batter2].strikeflag=1;
	            }
			}
			system("cls");
            printf("\n\n\n\t\t SELECT BOWLER\n\n");
            printf("\tID  Name        Overs      Wickets     Runs given       Economy\n");
            float oversbowled;
            int j;
            for( j=1;j<=11;j++)
            {
            	oversbowled = Balls_to_Overs(bowl[j].ballsbowled);
                printf("\t%-3d %-10s: %.2f        %-3d        %-3d             %.2f \n",bowl[j].id,bowl[j].name,oversbowled,bowl[j].wickets,bowl[j].runsgiven, bowl[j].economy);
            }
            printf("\n\n\tEnter BOWLER ID (1-11): ");
            scanf("%d",&bowlid);
            bowlid=bowlid;
            if(ballsbowled>5)
                SwitchPlayer();
            bowl[bowlid].bowlingflag=1;
        }

        int no_of_out=0;

        label:
        if(ballsbowled<totalovers*6)
        {
            system("cls");
            ViewScoreCard();
            printf("\n\n\tEnter Ball(1-6 runs, 'w' for out): ");
            scanf(" %c",&ballruns);
            if(ballruns=='0')
            {
                ballrun='0'-'0';
                bat[strikebatsman].runs+=0;
                bat[strikebatsman].ballsfaced++;
                bowl[bowlid].ballsbowled++;
                bowl[bowlid].runsgiven+=0;
                bowl[bowlid].economy = (float)bowl[bowlid].runsgiven/Balls_to_Overs(bowl[bowlid].ballsbowled);
		        bat[strikebatsman].strikerate = ((float)bat[strikebatsman].runs/(float)bat[strikebatsman].ballsfaced)*100.00;
            } else if(ballruns=='1')
            {
                ballrun='1'-'0';
                bat[strikebatsman].runs+=1;
                bat[strikebatsman].ballsfaced++;
                bowl[bowlid].ballsbowled++;
                bowl[bowlid].runsgiven+=1;
                bowl[bowlid].economy = (float)bowl[bowlid].runsgiven/Balls_to_Overs(bowl[bowlid].ballsbowled);
		        bat[strikebatsman].strikerate = ((float)bat[strikebatsman].runs/(float)bat[strikebatsman].ballsfaced)*100.00;
                SwitchPlayer();
            } else if(ballruns=='2')
            {
                ballrun='2'-'0';
                bat[strikebatsman].runs+=2;
                bat[strikebatsman].ballsfaced++;
                bowl[bowlid].ballsbowled++;
                bowl[bowlid].runsgiven+=2;
                bowl[bowlid].economy = (float)bowl[bowlid].runsgiven/Balls_to_Overs(bowl[bowlid].ballsbowled);
		        bat[strikebatsman].strikerate = (bat[strikebatsman].runs/bat[strikebatsman].ballsfaced)*100;
            } else if(ballruns=='3')
            {
                ballrun='3'-'0';
                bat[strikebatsman].runs+=3;
                bat[strikebatsman].ballsfaced++;
                bowl[bowlid].ballsbowled++;
                bowl[bowlid].runsgiven+=3;
                bowl[bowlid].economy = (float)bowl[bowlid].runsgiven/Balls_to_Overs(bowl[bowlid].ballsbowled);
		        bat[strikebatsman].strikerate = ((float)bat[strikebatsman].runs/(float)bat[strikebatsman].ballsfaced)*100.00;
                SwitchPlayer();
            } else if(ballruns=='4')
            {
                ballrun='4'-'0';
                bat[strikebatsman].runs+=4;
                bat[strikebatsman].ballsfaced++;
                bowl[bowlid].ballsbowled++;
                bowl[bowlid].runsgiven+=4;
                bowl[bowlid].economy = (float)bowl[bowlid].runsgiven/Balls_to_Overs(bowl[bowlid].ballsbowled);
		        bat[strikebatsman].strikerate = ((float)bat[strikebatsman].runs/(float)bat[strikebatsman].ballsfaced)*100.00;
            } else if(ballruns=='5')
            {
                ballrun='5'-'0';
                bat[strikebatsman].runs+=5;
                bat[strikebatsman].ballsfaced++;
                bowl[bowlid].ballsbowled++;
                bowl[bowlid].runsgiven+=5;
				bowl[bowlid].economy = (float)bowl[bowlid].runsgiven/Balls_to_Overs(bowl[bowlid].ballsbowled);
		        bat[strikebatsman].strikerate = ((float)bat[strikebatsman].runs/(float)bat[strikebatsman].ballsfaced)*100.00;
                SwitchPlayer();
			} else if(ballruns=='6')
            {
                ballrun='6'-'0';
                bat[strikebatsman].runs+=6;
                bat[strikebatsman].ballsfaced++;
                bowl[bowlid].ballsbowled++;
                bowl[bowlid].runsgiven+=6;
		        bowl[bowlid].economy = (float)bowl[bowlid].runsgiven/Balls_to_Overs(bowl[bowlid].ballsbowled);
		        bat[strikebatsman].strikerate = ((float)bat[strikebatsman].runs/(float)bat[strikebatsman].ballsfaced)*100.00;
            } else if(ballruns=='w'||ballruns=='W')
            {
                bat[strikebatsman].outstatus=1;
                bowl[bowlid].wickets++;
                bowl[bowlid].ballsbowled++;
                int a;
                for( a=1;a<=11;a++)
                {
                    if(bat[a].outstatus==1)
                    no_of_out++;
                }
                if(no_of_out==10)
                {
                    ballsbowled++;
                    system("cls");
                    printf("\n\n\tFINAL SCORESHEET");
                    ViewScoreCard();
                    getch();
                    break;
                }
                bat[strikebatsman].strikeflag=0;
                printf("\tBatsman %d: %s is out.",bat[strikebatsman].id,bat[strikebatsman].name);
                first:
                printf("\n\tEnter next batsman ID (1-11): ");
                scanf("%d",&nb);
                if(bat[nb].strikeflag)
                {
                    printf("\tBatsman %d:%s is already batting.\n\tENTER AGAIN",bat[nb].id,bat[nb].name);
                    goto first;
                }
                if(bat[nb].outstatus)
                {
                    printf("\tBatsman %d:%s is already out.\n\tENTER AGAIN",bat[nb].id,bat[nb].name);
                    goto first;            
                }
                bat[strikebatsman].ballsfaced++;
                bat[nb].strikeflag=1;
                strikebatsman=nb;
            } else if(ballruns == 'v'||ballruns=='V')
			{
				ballrun='1'-'0';
				ballsbowled--;
				bowl[bowlid].runsgiven+=1;
		        bowl[bowlid].economy = (float)bowl[bowlid].runsgiven/bowl[bowlid].ballsbowled;
			}else
            {
                printf("\n\tInvalid input.ENTER AGAIN.");
                goto label;
            }
        }
        if(ballsbowled==totalovers*6)
        {
            system("cls");
            printf("\n\n\tFINAL SCORECARD");
            ViewScoreCard();
            getch();
        }
        ballsbowled++;
        score=score+ballrun;
        
        
   }
   
}

//Function to set default values
void SetDefaultScores()
{
    int player;
	for( player =1;player<=11;player++)
    {
        bat[player].ballsfaced=0;
		bat[player].outstatus=0;
		bat[player].runs=0;
		bat[player].outstatus=0;
		bat[player].strikeflag=0;
		bat[player].strikerate = 0;
		bowl[player].economy=0.0;
		bowl[player].ballsbowled=0;
		bowl[player].runsgiven=0;
		bowl[player].wickets=0;
		bowl[player].bowlingflag=0;
    }
}

void ViewScoreCard()
{
    printf("\n\n\tBATTING TEAM STATISTICS:\n\n");
    int playerindex;
    printf("\tID  Name      Runs    Balls  Strike Rate\n");
    for( playerindex = 1; playerindex<=11;playerindex++)
    {
        if(bat[playerindex].outstatus)
        	printf("\t%-3d%-10s: %-3d      %-3d       %.2f        OUT\n",bat[playerindex].id,bat[playerindex].name,bat[playerindex].runs,bat[playerindex].ballsfaced, bat[playerindex].strikerate);
        else 
        {
            if(playerindex==strikebatsman)
            printf("\t%-3d%-10s: %-3d      %-3d       %.2f        NOT-OUT  *Strike\n",bat[playerindex].id,bat[playerindex].name,bat[playerindex].runs,bat[playerindex].ballsfaced, bat[playerindex].strikerate);
            else if(playerindex==nonstrikebatsman)
            printf("\t%-3d%-10s: %-3d      %-3d       %.2f        NOT-OUT  *Non Strike\n",bat[playerindex].id,bat[playerindex].name,bat[playerindex].runs,bat[playerindex].ballsfaced, bat[playerindex].strikerate);
            else
            printf("\t%-3d%-10s: %-3d      %-3d       %.2f        YET-TO-BAT\n",bat[playerindex].id,bat[playerindex].name,bat[playerindex].runs,bat[playerindex].ballsfaced, bat[playerindex].strikerate);
            
        }
    }
    printf("\n\tBOWLING TEAM STATISTICS:\n\n");
    int j;
	float overbowled;
	printf("\tID  Name         Overs   Wickets   Runs given  Economy\n");
    for( j =1;j<=11;j++)
    {
        if(bowl[j].bowlingflag)
        {
        	overbowled=Balls_to_Overs(bowl[j].ballsbowled);
            printf("\t%-3d%-10s: %.2f        %-3d       %-3d         %.2f\n",bowl[j].id,bowl[j].name,overbowled,bowl[j].wickets, bowl[j].runsgiven, bowl[j].economy);
    	}
    }
    float ov;
    ov=Balls_to_Overs(ballsbowled);
    printf("\n\t\tOVERS: %.2f", ov);
    printf("\n\t\tSCORE: %d",score);
}

float Balls_to_Overs(int balls)
{
    int o=0,b=0;
    o=balls/6;
    b=(balls%6)/10;
    return o+b;
}

void SwitchPlayer()
{
    int temp=0;
    temp=strikebatsman;
    strikebatsman=nonstrikebatsman;
    nonstrikebatsman=temp;
}
