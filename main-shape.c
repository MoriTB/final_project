#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>
int main()
{
  // printf("-\n");
  // printf(" |\n");
    int i=0 ,j=0,blocks_number;
    bool check_true_false=0;
    int counter2=0;
    int counter=0;

    scanf("%d",&blocks_number);
    int original_block_number;
    original_block_number=blocks_number;
    blocks_number*=4;
    blocks_number++;
    char visual_map[blocks_number+2][blocks_number];
  

          
      for (i = 0; i <blocks_number; i++)
       { for (j = 0; j <blocks_number; j++)
        {
          if((i%4==2)&&(j%4==0))
            counter2++;
         if ((j%4==0)&&(i%4==0))
          counter++;
          if ((i%4==0)&&(j%4==0))
            visual_map[i][j]='.';
          else if ((i%4==0)&&(counter%2!=0)&&(j%4!=0))
            visual_map[i][j]='.';
          else if((i%4==0)&&(counter%2==0)&&(j%4!=0))
            visual_map[i][j]=' ';
           else if ((i%4==1)&&(j%4==0))
           {
            visual_map[i][j]='.';
           }
          else if ((i%4==1)&&(j%4!=0))
            {
              visual_map[i][j]=' ';
            }
          else if ((i%4==2)&&(j%4==0))
          {
            visual_map[i][j]='.';
          }
          else if ((i%4==2)&&(counter2%2==0)&&(j%4!=0))
          {
            visual_map[i][j]='.';
          }
          else if ((i%4==2)&&(counter2%2!=0)&&(j%4!=0))
          {
            visual_map[i][j]=' ';
          }
          else if ((i%4==3)&&((j%4==0)))
           {
            visual_map[i][j]='.';
           }
          else if ((i%4==3)&&(j%4!=0))
            {
              visual_map[i][j]=' ';
            }
        }
        counter=0;
        counter2=0;
       } 
       i=blocks_number;
      for(j=0;j<blocks_number;j++)
      {
        if ((j%4!=0)||(j==0))
        visual_map[i][j]=' ';
        else
        {
          visual_map[i][j]='.';
        }
      }
      counter=0;
      for(j=0;j<blocks_number;j++)
      {
        if (j%4==0)
        {
          counter++;
        }
        if((j%4==0)&&(j!=0))
          visual_map[blocks_number+1][j]='.';
        else if(j==0)
          visual_map[blocks_number+1][j]=' ';
        else if((j%4!=0)&&(counter%2!=0))
        {
          visual_map[blocks_number+1][j]=' ';
        }
        else
        {
          visual_map[blocks_number+1][j]='.';
        }
        if (original_block_number%2==0)
          {
            visual_map[0][blocks_number-1]=' ';
            visual_map[1][blocks_number-1]=' ';
          }
        else
        {
          visual_map[blocks_number][blocks_number-1]=' ';
          visual_map[blocks_number+1][blocks_number-1]=' ';
        }
        
      }

  
for(i=0;i<=blocks_number+1;i++)
  { 
      {
       for(j=0;j<blocks_number;j++)
        printf(" %c ",visual_map[i][j]);
      } 
    printf("\n");
  }
}