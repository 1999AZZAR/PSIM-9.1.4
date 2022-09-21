#ifndef _CH_DIRENT_H_
#define _CH_DIRENT_H_

#define _NAME_MAX 255 

struct dirent {
  char  d_name[_NAME_MAX + 1];
};

struct _DIR
{
  char          *dir_name;
  int           just_opened;
  unsigned int find_file_handle;
  void *        find_file_data;
  struct dirent readdir_result;
}; 
typedef struct _DIR DIR;

#endif
