//--------------------------------------------------------------------------
/**
 * @file readBinary.cpp
 * @ingroup
 * @brief read binary file
 * @author himo
 */
//--------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

template<typename T>
int fileRead(const std::string fname, const int length, T* data);
void setArgs(int argc, char *argv[], std::string &fname, int &length, bool &endianFlg);
void usage();
bool machine_is_little_endian(void);
void endian_convert(const double* buf, const int len);


int main(int argc, char *argv[])
{
  std::cout <<"start"<<std::endl;

  if(  machine_is_little_endian())
  {
      std::cout << "@@@ this machine is little endian"<<std::endl;
  }
  else
  {
      std::cout << "@@@ this machine is big endian"<<std::endl;
  }

  std::string fname;
  int length = 500;
  bool endianFlg = false;
  int fileLength = 0;
  setArgs(argc, argv, fname, length, endianFlg);

  double *data = new double[length];
fileLength = fileRead(fname, length, data);

  if(endianFlg == true ) {endian_convert(data, length);}
  for (int i = 0; i < length && i< fileLength; i++)
  {
    printf("%1.16d %+1.16e\n", i, data[i]);
  }
  delete [] data;

  std::cout <<"END ALL"<<std::endl;
  return 0;
}


//--------------------------------------------------------------------------
/**
 * @brief analysing args
 */
//--------------------------------------------------------------------------
void setArgs(int argc, char *argv[], std::string &fname, int &length, bool &endianFlg)
{
  argc -=1;  argv +=1;
  if(argc != 2 && argc != 4 && argc != 6 ){usage();}
  while(argc > 0){
    if( std::string(argv[0]) == "-f")
    {
      fname  = std::string(argv[1]);
            std::cout <<"@@@ ARG: -f    = "<< fname<<std::endl;
      argc  -= 2; argv +=2;
      continue;
    }
    if(std::string(argv[0]) =="-l")
    {
      length = atoi(argv[1]);
            std::cout <<"@@@ ARG: -l    = "<< length<<std::endl;
      argc-=2; argv+=2;
      continue;
    }
    if(std::string(argv[0]) =="-e")
    {
      if (std::string(argv[1]) == "true")
      {
        endianFlg = true;
      }
      else if (std::string(argv[1]) == "false"){}
      else {
              std::cout << "@@@ ARG: -e    =  sholud ture or false"<<std::endl;
        exit(1);
      }
      std::cout.setf(std::ios::boolalpha);
      std::cout <<"@@@ ARG: -e    = "<< endianFlg<<std::endl;
      argc-=2; argv+=2;
    }
  }
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void usage()
{
  fprintf(stderr,
          "usage: [OPTIONS] <gauge config>\n"
          "OPTIONS:\n"
          "\t-f file name (must need)\n"
          "\t-l print out length\n"
          "\t-e endian flg (true or false)\n"
          "\t          If this option is used, analysis of args is terminated\n");
  exit(1);
}

//--------------------------------------------------------------------------
/**
 * @brief read data
 */
//--------------------------------------------------------------------------
template<typename T>
int fileRead(const std::string fname, const int length, T* data)
{
  std::fstream infile;

  infile.open(fname.c_str(),std::ios::in|std::ios::binary);
    if (!infile.is_open()) {
      std::cout << "ERROR file can't open (no exist)::"<<fname<<std::endl;
      exit(1);
    }
    if (infile.fail()){
      std::cout << "ERROR file size is 0 (can open)::"<<fname<<std::endl;
      exit(1);
    }

    int id = 0;
    while(!infile.eof())
    {
      infile.read( ( char * ) &(data[id]), sizeof( T ) );
    if (id == length) break;
    id=id+1;
    }
    id--;
    static int tmp = 0;
    if (tmp==0) {
      std::cout <<"reading binary data size is_open;;"<<id<<std::endl;
      tmp=tmp+1;
    }
    infile.close();
  return id;
}

//--------------------------------------------------------------------------
/**
 * @brief check endian
 */
//--------------------------------------------------------------------------

bool machine_is_little_endian(void)
{
  int int0=0;
  *((char*) &int0)=1;
  if (int0==1)
    return true;
  else
    return false;
}

//--------------------------------------------------------------------------
/**
 * @brief convert endian
 */
//--------------------------------------------------------------------------
void endian_convert(const double* buf, const int len)
{
  for(int i=0; i<len; i++){
    char tmp[8];
    ((double*)tmp)[0] = *buf;
    for(int j=0; j<8; j++){
      ((char*)buf)[j] = ((char*)tmp)[7-j];
    }
    buf++;
  }
}
//--------------------------------------------------------------------------
