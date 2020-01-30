#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define max 5
#define maxx 100
struct shift_cube
{
    int x,y,type,capacity,activate;
};
struct shift_cube backend[10][10];

struct cells
{
    char name[max];
    int x ,y,energy;
};
struct node
{
    struct cells cell;
    struct node *next;
};
int type_print[7];
int move_option;
char *name_move_option[6];
void name_generator(char *name,int length);
int location_generation(int high_max);
struct node * create_node(int maximation);
void add_end(struct node **list, struct node *new_nodes);
void visual_creator(int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_blocks_number);
void print(int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void add_data_file(int blocks_number,char visual_map[blocks_number+2][blocks_number],int real_blocks_number,char *inname);
void add_cells(int cell_number,int blocks_number,char visual_map[blocks_number+2][blocks_number],struct node *player,int original_block_number);
struct node * add_cells2(int cell_number,int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_block_number);
void move_north(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void move_north_west(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void move_north_east(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void move_south(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void move_south_east(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void move_south_west(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void check_movment(struct node *current,int original_block_number);
void move_cell(int third_choice,struct node *current,int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void printer_jologiry_tkrar(void);
void print_list(struct node *list);
struct node  * creat_node_manual(int x,int y,int energy);
int main()
{
  srand(time(NULL));
  int choice;
  int cells_number;
  char name[maxx];
  while(1)
    {
      printf("[1]load\n");
      printf("[2]single player\n");
      printf("[3]multiplayer\n");
      printf("[4]exit\n");
      scanf("%d",&choice);
      if (choice==2)
         {
           printf("so whats the address of the main blank file \n");
           scanf("%s",name);
           printf("how many cell you got boi?\n");
           scanf("%d",&cells_number);
           break;
         }


    }
  int i,j;
    int blocks_number;
    if(choice==2)
   { 
     int third_choice;
     int choice_second;
     int choice_second_second;
     struct node *current=NULL;
     FILE *fstr;
    fstr=fopen(name,"rb");
    if (fstr==NULL)
      {
        printf("the address you gave me wasnt right bud !");
        return -1;
      }
    fread(&blocks_number,sizeof(int),1,fstr);
    int original_block_number;
    original_block_number=blocks_number;
    blocks_number*=4;
    blocks_number++;
    char visual_map[blocks_number+2][blocks_number];
    visual_creator(blocks_number,visual_map,original_block_number);
    add_data_file(blocks_number,visual_map,original_block_number,name);
    struct node *player101=add_cells2(cells_number,blocks_number,visual_map,original_block_number);
    print(blocks_number,visual_map);
    printf("\n");
    printf("which cell you want to move my lord ?\n");
    fclose(fstr);
    int counter=1;
    for(current=player101;current!=NULL;current=current->next)
    {
      printf("[%d]%s (%d,%d)\n",counter,current->cell.name,current->cell.x,current->cell.y);
      counter++;
    }
    counter=1;
    scanf("%d",&choice_second);
    current=player101;
    while(counter<choice_second)
    {
      current=current->next;
      counter++;
    }
    int menu_looker;
    if ((backend[current->cell.x][current->cell.y].type==1)&&(backend[current->cell.x][current->cell.y].capacity!=0))
    {
      printf("[1]move the cell\n");
      printf("[2]boost energy\n");
      printf("[3]save\n");
      printf("[4]change the name of the cell\n");
      printf("[5]exit\n");
      scanf("%d",&choice_second_second);
      menu_looker=1;
    }
    else if ((backend[current->cell.x][current->cell.y].type==2)&&(current->cell.energy>=80))
    {
      printf("[1]move the cell\n");
      printf("[2]split the cell \n");
      printf("[3]save\n");
      printf("[4]change the name of the cell\n");
      printf("[5]exit\n");
      scanf("%d",&choice_second_second);
      menu_looker=2;
    }
    else
    {
      printf("[1]move the cell\n");
      printf("[2]save\n");
      printf("[3]change the name of the cell\n");
      printf("[4]exit\n");
      scanf("%d",&choice_second_second);
      menu_looker=3;
    }
    
    if(choice_second_second==1)
    {
      check_movment(current,original_block_number);
      printer_jologiry_tkrar();
      scanf("%d",&third_choice);
      move_cell(third_choice,current,blocks_number,visual_map);
      system("clear");
      print(blocks_number,visual_map);
      sleep(3);
   }
   else if ((choice_second_second==2)&&(menu_looker==1))
   {
     int energy_boost;
      printf("how much energy you want to get from this block?(notice:the maximum energy you could get in one move is 15 points)\n");
      scanf("%d",&energy_boost);
      if(energy_boost>15)
      {
        printf("you have tried to get more than 15 but thats not possible therefore your cell got 15 points \n");
        backend[current->cell.x][current->cell.y].capacity-=15;
        current->cell.energy+=15;
      }
      else
      {
        printf("your cell has consumed %d energy from the block of enrgy \n",energy_boost);
         backend[current->cell.x][current->cell.y].capacity-=energy_boost;
        current->cell.energy+=energy_boost;
      }
   }
   else if((choice_second_second==2)&&(menu_looker==2))
   {
     
   }
}
}
void name_generator(char *name,int length)
{
     char charset[] ="abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int index;
    while (length-- > 0) {
          index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *name++ = charset[index];
    }
    *name = '\0';
}
int location_generation(int high_max)
{
    int location;
    location=(rand()%(high_max));
    return location;
}
struct node * create_node(int maximation)
{
 struct node * nn;
 nn = (struct node *)malloc(sizeof(struct node));
 name_generator(nn->cell.name,max);
 while(1)
 {
   nn->cell.x=location_generation(maximation);
  nn->cell.y=location_generation(maximation);
  if ((backend[nn->cell.x][nn->cell.y].activate==0)&&(backend[nn->cell.x][nn->cell.y].type!=3))
    break;
 }
 backend[nn->cell.x][nn->cell.y].activate=1;
 nn->next=NULL;
 return nn;
}
void add_end(struct node **list, struct node *new_nodes)
{
  struct node *current;
  for(current=*list;current->next!=NULL;current=current->next);
  current->next=new_nodes;
  new_nodes->next=NULL;
}
void visual_creator(int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_block_number)
{
  int i=0 ,j=0;
    
    bool check_true_false=0;
    int counter2=0;
    int counter=0;
      for (i = 0; i <blocks_number; i++)
       { for (j = 0; j <blocks_number; j++)
        {
          if((i%4==2)&&(j%4==0))
            counter2++;
         if ((j%4==0)&&(i%4==0))
          counter++;
          if ((i%4==0)&&(j%4==0))
            visual_map[i][j]='z';
          else if ((i%4==0)&&(counter%2!=0)&&(j%4!=0))
            visual_map[i][j]='z';
          else if((i%4==0)&&(counter%2==0)&&(j%4!=0))
            visual_map[i][j]=' ';
           else if ((i%4==1)&&(j%4==0))
           {
            visual_map[i][j]='z';
           }
          else if ((i%4==1)&&(j%4!=0))
            {
              visual_map[i][j]=' ';
            }
          else if ((i%4==2)&&(j%4==0))
          {
            visual_map[i][j]='z';
          }
          else if ((i%4==2)&&(counter2%2==0)&&(j%4!=0))
          {
            visual_map[i][j]='z';
          }
          else if ((i%4==2)&&(counter2%2!=0)&&(j%4!=0))
          {
            visual_map[i][j]=' ';
          }
          else if ((i%4==3)&&((j%4==0)))
           {
            visual_map[i][j]='z';
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
          visual_map[i][j]='z';
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
          visual_map[blocks_number+1][j]='z';
        else if(j==0)
          visual_map[blocks_number+1][j]=' ';
        else if((j%4!=0)&&(counter%2!=0))
        {
          visual_map[blocks_number+1][j]=' ';
        }
        else
        {
          visual_map[blocks_number+1][j]='z';
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
}
void print(int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
  int i,j;
  for(i=0;i<=blocks_number+1;i++)
  { 
      {
       for(j=0;j<blocks_number;j++)
       {
         if (visual_map[i][j] == 'z')
         {
           printf(" ❑ ");
           continue;
         }
         if (visual_map[i][j]=='V')
         {
           printf(" ☢︎ ");
           continue;
         }
        printf(" %c ",visual_map[i][j]);
       }
      } 
    printf("\n");
  }
}
void add_data_file(int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_block_number,char *inname)
{
    int i,j;
    int n;
    char what;
    int temporary_array[10][10];
    FILE *fop;
    fop=fopen(inname,"rb");
    if (fop==NULL)
        {
            printf("the file havent been found yet \n");
        }
        //chra ye add bishtar mikhune ? on az koja miad ? baraye chi vojod dare?
    fread(&n,sizeof(int),1,fop);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
             fread(&what,sizeof(unsigned char),1,fop);
             temporary_array[i][j]=what-'0';
        }
    }
  int stable_y=2;
       int stable_x;
  for(i=0;i<original_block_number;i++)
    {
        if(i%2==0)
             stable_x=blocks_number+1;
        else
        {
            stable_x=blocks_number+3;
        }
        
        for(j=0;j<original_block_number;j++)
        {
            if (i%2==0)
                {
                    stable_x-=4;
                    backend[i][j].x=stable_x;
                    backend[i][j].y=stable_y;
                    backend[i][j].type=temporary_array[i][j];
                    if (backend[i][j].type==1)
                        backend[i][j].capacity=100;
                    else
                    {
                        backend[i][j].capacity=0;
                    }
                    
                }
            else
            {
                stable_x-=4;
                backend[i][j].x=stable_x;
                    backend[i][j].y=stable_y;
                    backend[i][j].type=temporary_array[i][j];
                    if (backend[i][j].type==1)
                        backend[i][j].capacity=100;
                    else
                    {
                        backend[i][j].capacity=0;
                    }
            }
            
        }

        stable_y+=4;
    }
    //tasire shklk ha va rbtashon ba backend
    for(i=0;i<original_block_number;i++)
    {
        for(j=0;j<original_block_number;j++)
        {
            if(backend[i][j].type==1)
            {
                visual_map[(backend[i][j]).x+1][(backend[i][j].y)-1]='e';
            }
            else  if(backend[i][j].type==2)
                visual_map[(backend[i][j]).x+1][(backend[i][j].y)-1]='m';
            else  if(backend[i][j].type==3)
             visual_map[(backend[i][j]).x+1][(backend[i][j].y)-1]='f';
            else  if(backend[i][j].type==4)
             visual_map[(backend[i][j]).x+1][(backend[i][j].y)-1]='n';
        }
    }
    fclose(fop);
}
/*void add_cells(int cell_number,int blocks_number,char visual_map[blocks_number+2][blocks_number],struct node *player,int original_block_number)
{
  int i;
struct node *current_out=NULL;
if (player==NULL)
{
  player=create_node(original_block_number);
}
for(i=1;i<cell_number;i++)
{
    add_end(&player,create_node(original_block_number));
}
for(current_out=player;current_out!=NULL;current_out=current_out->next)
   {
    visual_map[backend[current_out->cell.x][current_out->cell.y].x][backend[current_out->cell.x][current_out->cell.y].y]='V';
    backend[current_out->cell.x][current_out->cell.y].activate=1;
   } 
   {
    
}*/
struct node * add_cells2(int cell_number,int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_block_number)
{
  int i;
  struct node *player=NULL;
struct node *current_out=NULL;

  player=create_node(original_block_number);

for(i=1;i<cell_number;i++)
{
    add_end(&player,create_node(original_block_number));
}
for(current_out=player;current_out!=NULL;current_out=current_out->next)
   {
    visual_map[backend[current_out->cell.x][current_out->cell.y].x][backend[current_out->cell.x][current_out->cell.y].y]='V';
    backend[current_out->cell.x][current_out->cell.y].activate=1;
   } 
   {
    
}
return player;
}
void check_movment(struct node *current,int original_block_number)
{
      //1 baraye inke move north ro neshon nade ast !
      if ((backend[current->cell.x][current->cell.y+1].type==3)||((current->cell.x>=original_block_number)||(current->cell.x<0)||(current->cell.y+1>=original_block_number)||(current->cell.y+1<0))||(backend[current->cell.x][current->cell.y+1].activate==1))
          type_print[0]=1;
      //2 baraye neshon nadadn move north west ast !
      if((current->cell.x%2==0)&&(((backend[current->cell.x-1][current->cell.y+1].type==3)||((current->cell.x-1>=original_block_number)||(current->cell.x-1<0)||(current->cell.y+1>=original_block_number)||(current->cell.y+1<0)))||(backend[current->cell.x-1][current->cell.y+1].activate==1)))
            type_print[1]=1;
      else if ((current->cell.x%2!=0)&&(((backend[current->cell.x-1][current->cell.y].type==3)||((current->cell.x-1>=original_block_number)||(current->cell.x-1<0)||(current->cell.y>=original_block_number)||(current->cell.y<0)))||(backend[current->cell.x-1][current->cell.y].activate==1)))
          type_print[1]=1;
      //3 baraye neshon nadadn move north east ast !
       if ((current->cell.x%2==0)&&(((backend[current->cell.x+1][current->cell.y+1].type==3)||((current->cell.x+1>=original_block_number)||(current->cell.x+1<0)||(current->cell.y+1>=original_block_number)||(current->cell.y+1<0)))||(backend[current->cell.x+1][current->cell.y+1].activate==1)))
          type_print[2]=1;
        else if ((current->cell.x%2!=0)&&(((backend[current->cell.x+1][current->cell.y].type==3)||((current->cell.x+1>=original_block_number)||(current->cell.x+1<0)||(current->cell.y>=original_block_number)||(current->cell.y<0)))||(backend[current->cell.x+1][current->cell.y].activate==1)))
          type_print[2]=1;
      //4 braye neshon nadadan move south ast !
       if (((backend[current->cell.x][current->cell.y-1].type==3)||((current->cell.x>=original_block_number)||(current->cell.x<0)||(current->cell.y-1>=original_block_number)||(current->cell.y-1<0)))||(backend[current->cell.x][current->cell.y-1].activate==1))
          type_print[3]=1;
      //5 baraye neshon nadadan move south west !
       if ((current->cell.x%2==0)&&(((backend[current->cell.x-1][current->cell.y].type==3)||((current->cell.x-1>=original_block_number)||(current->cell.x-1<0)||(current->cell.y>=original_block_number)||(current->cell.y<0)))||(backend[current->cell.x-1][current->cell.y].activate==1)))
          type_print[4]=1;
        else if ((current->cell.x%2!=0)&&(((backend[current->cell.x-1][current->cell.y-1].type==3)||((current->cell.x-1>=original_block_number)||(current->cell.x-1<0)||(current->cell.y-1>=original_block_number)||(current->cell.y-1<0)))||(backend[current->cell.x-1][current->cell.y-1].activate==1)))
          type_print[4]=1;
      //6 baraye neshon nadadn move south east !
       if ((current->cell.x%2==0)&&(((backend[current->cell.x+1][current->cell.y].type==3)||((current->cell.x+1>=original_block_number)||(current->cell.x+1<0)||(current->cell.y>=original_block_number)||(current->cell.y<0)))||(backend[current->cell.x+1][current->cell.y].activate==1)))
          type_print[5]=1;
        else if ((current->cell.x%2!=0)&&(((backend[current->cell.x+1][current->cell.y-1].type==3)||((current->cell.x+1>=original_block_number)||(current->cell.x+1<0)||(current->cell.y-1>=original_block_number)||(current->cell.y-1<0)))||(backend[current->cell.x+1][current->cell.y-1].activate==1)))
          type_print[5]=1;
}
void move_north(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
  if ((backend[target_cell->cell.x][target_cell->cell.y+1].activate==0)&&(backend[target_cell->cell.x][target_cell->cell.y+1].type!=3))
 { visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
  backend[target_cell->cell.x][target_cell->cell.y].activate=0;
  (target_cell->cell.y)++;
  visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
  backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  
 }
}
void move_north_west(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
  if(target_cell->cell.x%2!=0)
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)--;
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
    
  }
  else
  {
     visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)--;
    (target_cell->cell.y)++;
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
    
  }
}
void move_north_east(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
  if(target_cell->cell.x%2!=0)
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)++;
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
  }
  else
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)++;
    (target_cell->cell.y)++;
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
  }
}
void move_south(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
  if((backend[target_cell->cell.x][target_cell->cell.y-1].activate==0)&&(backend[target_cell->cell.x][target_cell->cell.y-1].type!=3))
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.y)--;
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
}
void move_south_east(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
  if(target_cell->cell.x%2==0)
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)++;
   visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
    
  }
  else
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)++;
    (target_cell->cell.y)--;
   visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
  
}
void move_south_west(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
  if(target_cell->cell.x%2==0)
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)--;
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
    
  }
  else
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)--;
    (target_cell->cell.y)--;
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
  
}
void printer_jologiry_tkrar(void)
{
  int i;
   char *name[6];
  name[0]="north";
  name[1]="north_west";
  name[2]="north_east";
  name[3]="south";
  name[4]="south_west";
  name[5]="south_east";
  for(i=0;i<6;i++)
  {
    if (type_print[i]==0)
    {
      move_option++;
      printf("[%d]%s\n",move_option,name[i]);
      name_move_option[move_option]=name[i];
    }
  }
}
void move_cell(int third_choice,struct node *current,int blocks_number,char visual_map[blocks_number+2][blocks_number])
{
if (third_choice>move_option)
        printf("there is no option for you ! :(\n");
      if (strcmp(name_move_option[third_choice],"north")==0)
        {
           move_north(current,blocks_number,visual_map);
        }
      else if (strcmp(name_move_option[third_choice],"north_west")==0)
       {
          move_north_west(current,blocks_number,visual_map);
       }
      else if (strcmp(name_move_option[third_choice],"north_east")==0)
       {
          move_north_east(current,blocks_number,visual_map);
       }
      else if (strcmp(name_move_option[third_choice],"south")==0)
        {
          move_south(current,blocks_number,visual_map);
        }
      else if (strcmp(name_move_option[third_choice],"south_west")==0)
         {
           move_south_west(current,blocks_number,visual_map);
         }
      else if (strcmp(name_move_option[third_choice],"south_east")==0)
         {
           move_south_east(current,blocks_number,visual_map);
         }
}
void print_list(struct node *list)
{
  int counter=1;
  struct node *current;
  for(current=list;current!=NULL;current=current->next)
    {
      printf("%d)%s (%d,%d) got %d energy \n",counter,current->cell.name,current->cell.x,current->cell.y,current->cell.energy);
      counter++;
    }
}
struct node * creat_node_manual(int x, int y,int energy)
{
  struct node *nn;
  nn->cell.x=x;
  nn->cell.y=y;
  nn->cell.energy=energy;
  name_generator(nn->cell.name,max);
  return nn;
}