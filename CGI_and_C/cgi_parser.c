#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int get_init(char *data, int flag)
{
  int length = -1;
  length = strlen(data);
  if(!flag) return length;
  printf("<h3><---------------DEBUG---------------></h3>");
  printf("<p>LENGTH: %d</p>", length);
  printf("<p>CONTENT:<br/>%s</p>",data);
  printf("<h3><---------------DEBUG---------------></h3>");
  return length;
}

char* post_init(unsigned long int lenstr, int flag)
{
  if(!lenstr) return NULL;
  char *data = NULL;
  int traverse = 0;
  data = (char *) malloc(sizeof(char)*(lenstr+1));
  if(fread(data,1,lenstr,stdin)!=lenstr) return NULL;
  if(!flag) return data;
  printf("<h2><---------------DEBUG---------------></h2>");
  printf("<p>LENGTH: %ld</p>", lenstr);
  printf("<p>CONTENT:<br/>");
  for(;*(data+traverse) != '\0';traverse++)
  {
    if(*(data+traverse) == 13) printf("\\r");
    else if(*(data+traverse) == 10) printf("\\n");
    else printf("%c", *(data+traverse));
  }
  printf("</p>");
  printf("<h2><---------------DEBUG---------------></h2>");
  return data;
}

char *clean_urlencode(char *data)
{
  int dec = 0,traverseOld = 0,traverseNew = 0;
  char hex[3];
  char *newdata;
  
  newdata = (char *) malloc((strlen(data)+1) * sizeof(char));
  
  hex[2] = '\0';
  for(;*(data+traverseOld) != '\0';traverseOld++,traverseNew++)
  {
    if(*(data+traverseOld) == '+') *(newdata+traverseNew) = ' ';
    else if(*(data+traverseOld) == '%')
    {
      hex[0] = *(data+(++traverseOld));
      hex[1] = *(data+(++traverseOld));
      sscanf(hex,"%x",&dec);
      *(newdata+traverseNew) = (char) dec;
    }
      else *(newdata+traverseNew) = *(data+traverseOld);
  }
  newdata = (char *) realloc(newdata,(traverseNew+1) * sizeof(char));
  *(newdata+traverseNew) = '\0';
  return newdata;
}

void load(char** line, char** input)
{
  int length = 1;
  free(*line);
  *line = (char *) malloc(sizeof(char)*length);
  **line = '\0';

  for(;1;(*input)++,length++)
  {
    if(**input != 13)
    {
      *line = (char *) realloc(*line,sizeof(char)*(length+1));
      *(*line+length) = '\0';
      *(*line+length-1) = **input;
    }
    else
    {
      *input = *input + 2;
      break;
    }
  }
}

char* parse_data(char *data, char *key, char *enctype)
{
  if(!strcmp(enctype, "urlencoded"))
  {
    int strpos = 0;
    char *workingData = NULL;
    workingData = strstr(data,key);
    if(workingData)
    {
      while(workingData != NULL && *(workingData + strlen(key)) != '=')
      {
        workingData = workingData + strlen(key);
        workingData = strstr(workingData,key);
      }
      if(workingData)
      {
        workingData = workingData + strlen(key) + 1;
        for(;*(workingData + strpos) != '&' && *(workingData + strpos) != '\0'; strpos++);
        *(workingData + strpos) = '\0';
      }
    }
    return workingData;
  }

  else if(!strcmp(enctype, "multipart/form-data"))
  {
    char *line = NULL;
    char *basis = NULL;
    char *name = NULL;

    int thesame = 0;

    load(&line,&data);
    basis = (char *) malloc(sizeof(char)*strlen(line)+1);
    strcpy(basis,line);

    for(;*(line+strlen(basis)) != '-' && *(line+strlen(basis)-1) != '-';load(&line,&data))
    {
      for(load(&line,&data); *line != '\0'; load(&line,&data))
      {
        if(*(line+8) == 'D')
        {
          name = strstr(line,key);
          if(!name) continue;
          *(name + strlen(key)) = '\0';
          if(!strcmp(name,key))
            thesame = 1;
        }
      }
      
      load(&line,&data);
      if(!strcmp(line,basis))
        load(&line,&data);
      else
      {
        if(thesame)
        {
          free(basis);
          return line;
        }
      }
    }
    free(basis);
    free(line);
  }
  return NULL;
}