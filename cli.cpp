#include <string.h>
#include "cli.h"



const char DELIMIT[]= ",";



char cmd_name[CMD_MAX_NUM][CMD_MAX_LEN];
int cmd_id[CMD_MAX_NUM];
DO_CMD_FUNC do_func[CMD_MAX_NUM];



int num_cmd = 0;




// Hien thi dau nhac lenh

void addCmd(int id, const char* name, DO_CMD_FUNC f)
{
    cmd_id[num_cmd]=id;
    do_func[num_cmd]=f;
    strcpy(cmd_name[num_cmd], name);
    num_cmd++;
}



// Ham phan tich cu phap

int parseCmd(char *sCmdBuf,  int& cmd_argc, char * cmd_argv[])
{
  // phan tich xau ki tu nguoi dung nhap vao de xac dinh lenh va tham so

  // Cu phap:  <ten lenh>space<tham so 1>space<tham so 2>
  //           Moi thanh phan cua lenh cach nhau 1 hoac nhieu dau space
  char * arg;
  cmd_argc = 0; // so tham so = 0
  arg = strtok (sCmdBuf,DELIMIT); // phan tich xau ki tu trong sCmdBuf
  while (arg != NULL)
  {
    cmd_argv[cmd_argc++] = arg;
    arg = strtok (NULL, DELIMIT);
  }
  int i;
  return cmd_argc;
}



void doCmd(int id, int cmd_argc, char * cmd_argv[])
{
     if(id==CMD_NOOP_ID || id==CMD_UNKNOWN_ID)
        return;
     else
     {
        void (*f)(char*[], int) = do_func[id];
        if(f!=NULL)
                (*f)(cmd_argc, cmd_argv);
     }
}




