#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define max 7
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
int first_load_info[3];//agha avali noe bazie dovomi neshon mide original blocks 3vomi ham blocks numbere 
int turn;
int type_print[7];
int move_option;
int loaded;
char *name_move_option[6];
char name_used_energy1[max];
char name_used_energy2[max];
void name_generator(char *name,int length);
int location_generation(int high_max);
struct node * create_node(int maximation);
void add_end(struct node *list, struct node *new_nodes);
void visual_creator(int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_blocks_number);
void print(int blocks_number,char visual_map[blocks_number+2][blocks_number]);
void add_data_file(int blocks_number,char visual_map[blocks_number+2][blocks_number],int real_blocks_number,char *inname);
struct node * add_cells2(int cell_number,int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_block_number);
void move_north(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe);
void move_north_west(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe);
void move_north_east(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe);
void move_south(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe);
void move_south_east(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe);
void move_south_west(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe);
void check_movment(struct node *current,int original_block_number);
void move_cell(int third_choice,struct node *current,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe);
void printer_jologiry_tkrar(void);
void deleteNode(struct node **list,struct node *current);
void print_list(struct node *list);
int check_around(int x,int y,int original_block_number);
void save(int noe ,int original_blocks_number,struct node *player,struct node * second_player,char *inname);
void load(char *inname,struct node *player,struct node *second_player);
struct node * creat_node_manual_load(int vorodi_x, int vorodi_y,char inname[max],int energy);
struct node  * creat_node_manual(int x,int y);
int main()
{
  int i;
  srand(time(NULL));
  int choice;
  char address_map[maxx]="/users/apple/desktop/ce_98/maps/";
  int cells_number,cells_number_2;
  struct node *player101=NULL,*player202=NULL;
  char name[maxx];
  char name_1[maxx];
  while(1)
    {
      printf("[1]load\n");
      printf("[2]single player\n");
      printf("[3]multiplayer\n");
      printf("[4]exit\n");
      scanf("%d",&choice);
      if (choice==1)
        {
         
          printf("which one your previous saved game you shall play ?\n give us the address my lady/my sir\n");
          scanf("%s",name_1);
          load(name_1,player101,player202);
          loaded=1;
          if (first_load_info[0]==1)
            choice=2;
          else
          {
            choice=3;
          }
          break;
        }
      if ((choice==2)&&(loaded==0))
         {
           printf("type the address of your basic map madam/sir?\n");
           scanf("%s",name);
           printf("how many cell you got my lady/my lord ?\n");
           scanf("%d",&cells_number);
           break;
         }
      else if (choice==4)
          {
            break;
          }
      else if ((choice==3)&&(loaded==0))
      {
        printf("what type of map you have in mind madam/sir?give us the full address \n");
        scanf("%s",name);
        printf("how many cell you got my lady/my lord ?\n");
        scanf("%d",&cells_number);
        printf("how about you tough lookin person ?\n");
           scanf("%d",&cells_number_2);
           break;
      }
    }
  int j;
    int blocks_number;
    if((choice==2)||(choice==3))
   {
        printf("it got through the first poll\n");
       int third_choice;
      int choice_second;
      int choice_second_second;
      struct node *current=NULL;
      if (loaded==0)
      {
        FILE *fstr;
        fstr=fopen(name,"rb");
        if (fstr==NULL)
        {
        printf("the address you gave me wasnt right bud !");
        return -1;
        }
      fread(&blocks_number,sizeof(int),1,fstr);
      fclose(fstr);
      }
      else
        blocks_number=first_load_info[1];
      int original_block_number;
      original_block_number=blocks_number;
      blocks_number*=4;
      blocks_number++;
      printf("before making the visual_map\n");
          char  visual_map[blocks_number+2][blocks_number];
      visual_creator(blocks_number,visual_map,original_block_number);
      printf("the visual map is created\n");
      if (loaded==0)
        add_data_file(blocks_number,visual_map,original_block_number,name);
    else
      {
         printf("%d     %d   \n",blocks_number,original_block_number);
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
      }
      printf("after making the visual map corrected with the backend\n");
      if ((choice==2)&&(loaded==0))
      { 
       player101=add_cells2(cells_number,blocks_number,visual_map,original_block_number);
      }
      else if (loaded==0)
      {
      player101=add_cells2(cells_number,blocks_number,visual_map,original_block_number);
      player202=add_cells2(cells_number_2,blocks_number,visual_map,original_block_number);
      }
    print(blocks_number,visual_map);
    printf("\n");
    int counter=1;
    int whose_turn=1;
    int turn_insider;
    while(1)
    {
      
      counter=1;   
      system("clear");
      print(blocks_number,visual_map);
    if ((whose_turn%2==0)&&(choice==3))
    {
        printf("which cell you want to move my lord ?\n");
      for(current=player202;current!=NULL;current=current->next)
      {
      printf("[%d]%s (%d,%d)\n",counter,current->cell.name,current->cell.x,current->cell.y);
      counter++;
      
      }
      counter=1;
      scanf("%d",&choice_second);
      current=player202;
      while(counter<choice_second)
      {
      current=current->next;
      counter++;
      }
      whose_turn++;
      turn_insider=2;
    }
    else
    {
        printf("which cell you want to move my lord ?\n");
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
      whose_turn++;
      turn_insider=1;
    }
      int menu_looker;
       if (((backend[current->cell.x][current->cell.y].type==1)&&(backend[current->cell.x][current->cell.y].capacity!=0)))
      {
        system("clear");
        print(blocks_number,visual_map);
        printf("[1]move the cell\n");
        printf("[2]boost energy\n");
        printf("[3]save\n");
        printf("[4]change the name of the cell\n");
        printf("[5]show statues of my cell\n");
        printf("[6]exit\n");
        scanf("%d",&choice_second_second);
        menu_looker=1;
      }
    else if ((backend[current->cell.x][current->cell.y].type==2)&&(current->cell.energy>=80)&&(check_around(current->cell.x,current->cell.y,original_block_number)==1))
      {
        system("clear");
        print(blocks_number,visual_map);
        printf("[1]move the cell\n");
        printf("[2]split the cell \n");
        printf("[3]save\n");
        printf("[4]change the name of the cell\n");
        printf("[5]show statues of my cell\n");
        printf("[6]exit\n");
        scanf("%d",&choice_second_second);
        menu_looker=2;
      }
      else
      {
        system("clear");
        print(blocks_number,visual_map);
        printf("[1]move the cell\n");
        printf("[2]save\n");
        printf("[3]change the name of the cell\n");
        printf("[4]show statues of my cell\n");
        printf("[5]exit\n");
        scanf("%d",&choice_second_second);
        menu_looker=3;
      }
    if(choice_second_second==1)
      {
        system("clear");
        print(blocks_number,visual_map);
        check_movment(current,original_block_number);
      
        printer_jologiry_tkrar();
        scanf("%d",&third_choice);
        move_cell(third_choice,current,blocks_number,visual_map,turn_insider);
        system("clear");
        print(blocks_number,visual_map);
        sleep(3);
      }
   else if ((choice_second_second==2)&&(menu_looker==1))
    {
      system("clear");
      print(blocks_number,visual_map);
      int energy_boost;
      printf("how much energy you want to get from this block?(notice:the maximum energy you could get in one move is 15 points)\n");
      scanf("%d",&energy_boost);
      if(energy_boost>15)
      {
        printf("%s cell had :%d\n",current->cell.name,current->cell.energy);
        backend[current->cell.x][current->cell.y].capacity-=15;
        current->cell.energy+=15;
        printf("%s cell now has %d\n",current->cell.name,current->cell.energy);
      }
      else
      {
         printf("%s cell has :%d\n",current->cell.name,current->cell.energy);
         backend[current->cell.x][current->cell.y].capacity-=energy_boost;
        current->cell.energy+=energy_boost;
         printf("%s cell has :%d\n",current->cell.name,current->cell.energy);
      }
      // if (turn_insider==1)
      //     strcat(name_used_energy1,current->cell.name);
      // else
      //     strcat(name_used_energy2,current->cell.name);
    sleep(3);
   }
   else if((choice_second_second==2)&&(menu_looker==2))
   {
     system("clear");
     print(blocks_number,visual_map);
     int tmp[2]={-1,1};
    add_end(player101,creat_node_manual(current->cell.x,current->cell.y));
      int random_number_x=location_generation(3)-1;
      int random_number_y=location_generation(3)-1;
    while(1)
    {
      if (current->cell.x%2==0)
      {
      random_number_y=(rand()%3)-1;
      if(random_number_y==-1)
        random_number_x=0;
      else if (random_number_y==0)
        random_number_x=tmp[rand()%2];
      else if(random_number_y==1)
        random_number_x=(rand()%3)-1;
      }
    else if (current->cell.x%2!=0)
      {
      random_number_y=(rand()%3)-1;
      if(random_number_y==1)
        random_number_x=0;
      else if (random_number_y==0)
        random_number_x=tmp[rand()%2];
      else if(random_number_y==-1)
        random_number_x=(rand()%3)-1;
      }
     if ((backend[current->cell.x+random_number_x][current->cell.y+random_number_y].activate==0)&&(backend[current->cell.x+random_number_x][current->cell.y+random_number_y].type!=3))
          break;
    }
    if (turn_insider==1)
      {
        visual_map[backend[current->cell.x+random_number_x][current->cell.y+random_number_y].x][backend[current->cell.x+random_number_x][current->cell.y+random_number_y].y]='V';
        backend[current->cell.x+random_number_x][current->cell.y+random_number_y].activate=1;
        add_end(player101,creat_node_manual(current->cell.x+random_number_x,current->cell.y+random_number_y));
        deleteNode(&player101,current);
      }
    else
    {
      visual_map[backend[current->cell.x+random_number_x][current->cell.y+random_number_y].x][backend[current->cell.x+random_number_x][current->cell.y+random_number_y].y]='V';
      backend[current->cell.x+random_number_x][current->cell.y+random_number_y].activate=1;
      add_end(player202,creat_node_manual(current->cell.x+random_number_x,current->cell.y+random_number_y));
      deleteNode(&player202,current);
    }
    system("clear");
    print(blocks_number,visual_map);
    printf("\n");
    if(turn_insider==1)
      print_list(player101);
    else
    {
      print_list(player202);
    }
    sleep(4);
    }
    if (((choice_second_second==3)&&(menu_looker!=3))||((choice_second_second==2)&&(menu_looker==3)))
    {
        char *name;
        name=(char * )malloc(sizeof(char )*maxx);
        char name_2[maxx];
        printf("under what name your file is going to be saved my lord\n");
        scanf("%s",name);
        save(choice-1,original_block_number,player101,player202,name);
    }
   if (((choice_second_second==4)&&(menu_looker!=3))||((choice_second_second==3)&&(menu_looker==3)))
    {
      
      char inname[max];
      printf("what is your chosen name dragonborn(5 letter only)\n");
      getchar();
      fgets(inname,maxx,stdin);
     for(i=0;i<max;i++)
      current->cell.name[i]=inname[i];
     
    }
    if(((choice_second_second==5)&&(menu_looker!=3))||((choice_second_second==4)&&(menu_looker==3)))
      {
        system("clear");
        print(blocks_number,visual_map);
        if (turn_insider==1)
         print_list(player101);
        else
        {
          print_list(player202);
        }
        
        sleep(5);
      }
      if(((choice_second_second==6)&&(menu_looker!=3))||((choice_second_second==5)&&(menu_looker==3)))
      {
        break;
      }
    for(i=0;i<6;i++)
    {
      name_move_option[i]='\0';
      type_print[i]=0;
    }
    move_option=0;
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
void add_end(struct node *list, struct node *new_nodes)
{
  struct node *current;
  for(current=list;current->next!=NULL;current=current->next);
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
           printf(" 🚧");
           continue;
         }
         if (visual_map[i][j]=='V')
         {
           printf(" 👾");
           continue;
         }
         if (visual_map[i][j]=='e')
          {
            printf(" 🔋");
            continue;
          }  
          if (visual_map[i][j]=='v')
          {
            printf(" 👻");
            continue;
          }
          if (visual_map[i][j]=='f')
          {
            printf(" ⛔");
            continue;
          }
          if (visual_map[i][j]=='m')
          {
            printf(" 🎏");
            continue;
          }
          if (visual_map[i][j]=='n')
          {
            printf(" 🏴");
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
struct node * add_cells2(int cell_number,int blocks_number,char visual_map[blocks_number+2][blocks_number],int original_block_number)
{
  int i;
  struct node *player=NULL;
struct node *current_out=NULL;

  player=create_node(original_block_number);

for(i=1;i<cell_number;i++)
  {
    add_end(player,create_node(original_block_number));
  }
if (turn%2==0)
  {
  for(current_out=player;current_out!=NULL;current_out=current_out->next)
   {
    visual_map[backend[current_out->cell.x][current_out->cell.y].x][backend[current_out->cell.x][current_out->cell.y].y]='V';
    backend[current_out->cell.x][current_out->cell.y].activate=1;
   }
  } 
  else
  {
    for(current_out=player;current_out!=NULL;current_out=current_out->next)
   {
    visual_map[backend[current_out->cell.x][current_out->cell.y].x][backend[current_out->cell.x][current_out->cell.y].y]='v';
    backend[current_out->cell.x][current_out->cell.y].activate=1;
   } 
  }
  turn++;
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
void move_north(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe)
{
  if ((backend[target_cell->cell.x][target_cell->cell.y+1].activate==0)&&(backend[target_cell->cell.x][target_cell->cell.y+1].type!=3))
 { visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
  backend[target_cell->cell.x][target_cell->cell.y].activate=0;
  (target_cell->cell.y)++;
  if (noe==1)
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
  else
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
  backend[target_cell->cell.x][target_cell->cell.y].activate=1;
 }
}
void move_north_west(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe)
{
  if(target_cell->cell.x%2!=0)
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)--;
    if (noe==1)
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
    {
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    }
    
    backend[target_cell->cell.x][target_cell->cell.y].activate=1; 
  }
  else
  {
     visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)--;
    (target_cell->cell.y)++;
    if (noe==1)
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
    {
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    }
    
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
}
void move_north_east(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe)
{
  if(target_cell->cell.x%2!=0)
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)++;
    if (noe==1)
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
    {
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    }
    
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
  else
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)++;
    (target_cell->cell.y)++;
     if (noe==1)
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
}
void move_south(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe)
{
  if((backend[target_cell->cell.x][target_cell->cell.y-1].activate==0)&&(backend[target_cell->cell.x][target_cell->cell.y-1].type!=3))
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.y)--;
    if (noe==1)
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
    {
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    }
    
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
}
void move_south_east(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe)
{
  if(target_cell->cell.x%2==0)
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)++;
    if (noe==1)
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
    {
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    }
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
  else
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)++;
    (target_cell->cell.y)--;
    if (noe==1)
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
    {
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    }
    backend[target_cell->cell.x][target_cell->cell.y].activate=1;
  }
}
void move_south_west(struct node *target_cell,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe )
{
  if(target_cell->cell.x%2==0)
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)--;
    if (noe==1)
        visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
    {
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    }
    backend[target_cell->cell.x][target_cell->cell.y].activate=1; 
  }
  else
  {
    visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]=' ';
    backend[target_cell->cell.x][target_cell->cell.y].activate=0;
    (target_cell->cell.x)--;
    (target_cell->cell.y)--;
    if (noe==1)
        visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='V';
    else
    {
      visual_map[backend[target_cell->cell.x][target_cell->cell.y].x][backend[target_cell->cell.x][target_cell->cell.y].y]='v';
    }
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
void move_cell(int third_choice,struct node *current,int blocks_number,char visual_map[blocks_number+2][blocks_number],int noe)
{
if (third_choice>move_option)
        printf("there is no option for you ! :(\n");
      if (strcmp(name_move_option[third_choice],"north")==0)
        {
           move_north(current,blocks_number,visual_map, noe);
        }
      else if (strcmp(name_move_option[third_choice],"north_west")==0)
       {
          move_north_west(current,blocks_number,visual_map, noe);
       }
      else if (strcmp(name_move_option[third_choice],"north_east")==0)
       {
          move_north_east(current,blocks_number,visual_map, noe);
       }
      else if (strcmp(name_move_option[third_choice],"south")==0)
        {
          move_south(current,blocks_number,visual_map, noe);
        }
      else if (strcmp(name_move_option[third_choice],"south_west")==0)
         {
           move_south_west(current,blocks_number,visual_map,noe);
         }
      else if (strcmp(name_move_option[third_choice],"south_east")==0)
         {
           move_south_east(current,blocks_number,visual_map,noe);
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
struct node * creat_node_manual(int vorodi_x, int vorodi_y)
{
  struct node *nm;
  nm = (struct node *)malloc(sizeof(struct node));
  nm->cell.x=vorodi_x;
  nm->cell.y=vorodi_y;
  nm->cell.energy=40;
  name_generator(nm->cell.name,max);
  nm->next=NULL;
  return nm;
}
struct node * creat_node_manual_load(int vorodi_x, int vorodi_y,char inname[max],int energy)
{
  int i;
  struct node *mm;
  mm = (struct node *)malloc(sizeof(struct node));
  mm->cell.x=vorodi_x;
  mm->cell.y=vorodi_y;
  mm->cell.energy=energy;
  for(i=0;i<max;i++)
    mm->cell.name[i]=inname[i];
    mm->cell.name[i]='\0';
  mm->next=NULL;
  return mm;
}
void deleteNode(struct node **list, struct node *current)
{
  struct node *temp=*list;
  struct node *ghabli;
  if ((temp!=NULL)&&(temp==current))
      {
        *list=temp->next;
        free(temp);
      }
  else 
    {
      while((temp!=NULL)&&(temp!=current))
      {
        ghabli=temp;
        temp=temp->next;
      }
      
    }
  if (temp==NULL)
    printf("the node in your link list wasnt found bod\n");
  ghabli->next=temp->next;
  free(temp);
  free(ghabli);
}
int check_around(int x, int y,int original_blocks_number)
{
  if (x%2==0)
  {
    if((backend[x-1][y].activate==0)&&(backend[x-1][y].type!=3)&&(x-1<original_blocks_number)&&(x-1>=0))
      return 1;
    else if ((backend[x][y-1].activate==0)&&(backend[x][y-1].type!=3)&&(y-1<original_blocks_number)&&(y-1>=0))
      return 1;
   else if ((backend[x+1][y].activate==0)&&(backend[x+1][y].type!=3)&&(x+1<original_blocks_number)&&(x+1>=0))
      return 1;
    else if ((backend[x-1][y+1].activate==0)&&(backend[x][y+1].type!=3)&&(x-1<original_blocks_number)&&(x-1>=0)&&(y+1<original_blocks_number)&&(y+1>=0))
      return 1;
    else if ((backend[x][y+1].activate==0)&&(backend[x][y+1].type!=3)&&(y+1<original_blocks_number)&&(y+1>=0))
      return 1;
    else if ((backend[x+1][y+1].activate==0)&&(backend[x+1][y+1].type!=3)&&(x+1<original_blocks_number)&&(x+1>=0)&&(y+1<original_blocks_number)&&(y+1>=0))
      return 1;
  }
  else
  {
    if((backend[x-1][y].activate==0)&&(backend[x-1][y].type!=3)&&(x-1<original_blocks_number)&&(x-1>=0))
      return 1;
    else if ((backend[x][y-1].activate==0)&&(backend[x][y-1].type!=3)&&(y-1<original_blocks_number)&&(y-1>=0))
      return 1;
    else if ((backend[x][y+1].activate==0)&&(backend[x][y+1].type!=3)&&(y+1<original_blocks_number)&&(y+1>=0))
      return 1;
    else if ((backend[x+1][y].activate==0)&&(backend[x+1][y].type!=3)&&(x+1<original_blocks_number)&&(x+1>=0))
      return 1;
    else if ((backend[x-1][y-1].activate==0)&&(backend[x-1][y-1].type!=3)&&(x-1<original_blocks_number)&&(x-1>=0)&&(y-1<original_blocks_number)&&(y-1>=0))
      return 1;
     else if ((backend[x+1][y-1].activate==0)&&(backend[x+1][y-1].type!=3)&&(x+1<original_blocks_number)&&(x+1>=0)&&(y-1<original_blocks_number)&&(y-1>=0))
      return 1;
  }
  return 2;
}
void save(int noe ,int original_blocks_number,struct node *player,struct node * second_player,char *inname)
{
  //noe 1 yani single player va noe 2 yani multiplayer 
  FILE *fop;
  struct node *current;
  fop=fopen(inname,"wb");
  if (fop==NULL)
  {
    printf("the file directory havent been found \n ");
  }
  int i,j,tedad_cell_player1=0,tedad_cell_player2=0;
  int blocks_number=original_blocks_number*4;
  blocks_number++;
  fwrite(&noe,sizeof(int),1,fop);
  fwrite(&original_blocks_number,sizeof(int),1,fop);
  fwrite(&blocks_number,sizeof(int),1,fop);
  if (noe==1)
    {
      for(current=player;current!=NULL;current=current->next)
      {
        tedad_cell_player1++;
      }
    }
   else
  {
    for(current=player;current!=NULL;current=current->next)
      {
        tedad_cell_player1++;
      }
    for(current=second_player;current!=NULL;current=current->next)
      {
        tedad_cell_player2++;
      }
  }
  fwrite(&tedad_cell_player1,sizeof(int),1,fop);
  fwrite(&tedad_cell_player2,sizeof(int),1,fop);
  for(i=0;i<=9;i++)
    {
      for(j=0;j<=9;j++)
      {
        fwrite(&backend[i][j],sizeof(struct shift_cube),1,fop);
      }
    }
  if (noe==1)
    {
      for(current=player;current!=NULL;current=current->next)
      {
        fwrite(current->cell.name,sizeof(char)*max,1,fop);
        fwrite(&current->cell.x,sizeof(int),1,fop);
        fwrite(&current->cell.y,sizeof(int),1,fop);
        fwrite(&current->cell.energy,sizeof(int),1,fop);
      }
    }
  else
  {
    for(current=player;current!=NULL;current=current->next)
      {
       fwrite(current->cell.name,sizeof(char)*max,1,fop);
        fwrite(&current->cell.x,sizeof(int),1,fop);
        fwrite(&current->cell.y,sizeof(int),1,fop);
        fwrite(&current->cell.energy,sizeof(int),1,fop);
      }
    for(current=second_player;current!=NULL;current=current->next)
      {
        fwrite(current->cell.name,sizeof(char)*max,1,fop);
        fwrite(&current->cell.x,sizeof(int),1,fop);
        fwrite(&current->cell.y,sizeof(int),1,fop);
        fwrite(&current->cell.energy,sizeof(int),1,fop);
      }
  }
  fclose(fop);
}
void load(char *inname,struct node *player,struct node *second_player)
{
  int i,j,tedad_player1,tedad_player2;
  char name[max];
  int x,y,energy;
  FILE *fop;
  fop=fopen(inname,"rb");
  int type_game,original_blocks_number,blocks_number;
  fread(&type_game,sizeof(int),1,fop);
  printf("type of game :%d\n",type_game);
  first_load_info[0]=type_game;
  fread(&original_blocks_number,sizeof(int),1,fop);
  printf("its %d by %d blocks\n",original_blocks_number,original_blocks_number);
  first_load_info[1]=original_blocks_number;
  fread(&blocks_number,sizeof(int),1,fop);
  first_load_info[2]=blocks_number;
  fread(&tedad_player1,sizeof(int),1,fop);
  fread(&tedad_player2,sizeof(int),1,fop);
  for(i=0;i<=9;i++)
  {
    for(j=0;j<=9;j++)
    {
      fread(&backend[i][j],sizeof(struct shift_cube),1,fop);
      printf("[%d][%d]= has %d\n",i,j,backend[i][j].capacity);
    }
  }
  if (type_game==1)
    {
        fread(name,sizeof(char)*max,1,fop);
        fread(&x,sizeof(int),1,fop);
        fread(&y,sizeof(int),1,fop);
        fread(&energy,sizeof(int),1,fop);
       if (player==NULL)
          player=creat_node_manual_load(x,y,name,energy);
      for(i=1;i<tedad_player1;i++)
      {
        fread(name,sizeof(char)*max,1,fop);
        fread(&x,sizeof(int),1,fop);
        fread(&y,sizeof(int),1,fop);
        fread(&energy,sizeof(int),1,fop);
        add_end(player,creat_node_manual_load(x,y,name,energy));
      }
    }
  else if ((type_game==2)&&(tedad_player2!=0))
  {

        fread(name,sizeof(char)*max,1,fop);
        fread(&x,sizeof(int),1,fop);
        fread(&y,sizeof(int),1,fop);
        fread(&energy,sizeof(int),1,fop);
      player=creat_node_manual_load(x,y,name,energy);
      for(i=1;i<tedad_player1;i++)
        {
        fread(name,sizeof(char)*max,1,fop);
        fread(&x,sizeof(int),1,fop);
        fread(&y,sizeof(int),1,fop);
        fread(&energy,sizeof(int),1,fop);
        add_end(player,creat_node_manual_load(x,y,name,energy));
        }
        fread(name,sizeof(char)*max,1,fop);
        fread(&x,sizeof(int),1,fop);
        fread(&y,sizeof(int),1,fop);
        fread(&energy,sizeof(int),1,fop);
      second_player=creat_node_manual_load(x,y,name,energy);
      for(i=1;i<tedad_player2;i++)
        {
        fread(name,sizeof(char)*max,1,fop);
        fread(&x,sizeof(int),1,fop);
        fread(&y,sizeof(int),1,fop);
        fread(&energy,sizeof(int),1,fop);
        add_end(second_player,creat_node_manual_load(x,y,name,energy));
        }
        
  }
  struct node *temp;
  for(temp=player;temp!=NULL;temp=temp->next)
          printf("%s cell is located at %d   and   %d  and has %d energy \n",temp->cell.name,temp->cell.x,temp->cell.y,temp->cell.energy);
        for(temp=second_player;temp!=NULL;temp=temp->next)
          printf("%s cell is located at %d   and   %d  and has %d energy \n",temp->cell.name,temp->cell.x,temp->cell.y,temp->cell.energy); 
  fclose(fop);
  sleep(7);
  system("clear");
}