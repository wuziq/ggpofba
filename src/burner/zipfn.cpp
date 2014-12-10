// Zip module
#include "burner.h"
#include "unzip.h"

static unzFile Zip=NULL;
static int nCurrFile=0; // The current file we are pointing to

int ZipOpen(char *szZip)
{
  Zip=unzOpen(szZip);
  if (Zip==NULL) return 1;
  unzGoToFirstFile(Zip); nCurrFile=0;
  return 0;
}

int ZipClose()
{
  if (Zip!=NULL) unzClose(Zip);  Zip=NULL;
  return 0;
}

// Get the contents of a zip file into an array of ZipEntrys
int ZipGetList(struct ZipEntry **pList,int *pnListCount)
{
  int nRet=0;
  int nNextRet=0;
  unz_global_info ZipGlobalInfo;
  struct ZipEntry *List=NULL; int nListLen=0;
  if (Zip==NULL) return 1;
  if (pList==NULL) return 1;

  memset(&ZipGlobalInfo,0,sizeof(ZipGlobalInfo));

  unzGetGlobalInfo(Zip,&ZipGlobalInfo);
  nListLen=ZipGlobalInfo.number_entry;

  // Make an array of File Entries
  List=(struct ZipEntry *)malloc(nListLen*sizeof(struct ZipEntry));
  if (List==NULL)  { unzClose(Zip); return 1; }
  memset(List,0,nListLen*sizeof(struct ZipEntry));

  nRet=unzGoToFirstFile(Zip); if (nRet!=UNZ_OK) { unzClose(Zip); return 1; }

  // Step through all of the files, until we get to the end

  for ( nCurrFile=0,          nNextRet=UNZ_OK;
        nCurrFile<nListLen && nNextRet==UNZ_OK;
        nCurrFile++,          nNextRet=unzGoToNextFile(Zip) )
  {
    unz_file_info FileInfo;
    char *szName=NULL;
    memset(&FileInfo,0,sizeof(FileInfo));

    nRet=unzGetCurrentFileInfo(Zip,&FileInfo,NULL,0,NULL,0,NULL,0); if (nRet!=UNZ_OK) continue;

    // Allocate space for the filename
    szName=(char *)malloc(FileInfo.size_filename+1); if (szName==NULL) continue;
    nRet=unzGetCurrentFileInfo(Zip,&FileInfo,szName,FileInfo.size_filename+1,NULL,0,NULL,0);

    List[nCurrFile].szName=szName;
    List[nCurrFile].nLen=FileInfo.uncompressed_size;
    List[nCurrFile].nCrc=FileInfo.crc;
  }

  // return the file list
  *pList=List;
  if (pnListCount!=NULL) *pnListCount=nListLen;

  unzGoToFirstFile(Zip); nCurrFile=0;
  return 0;
}

int ZipLoadFile(unsigned char *Dest,int nLen,int *pnWrote,int nEntry)
{
  int nRet=0;
  if (Zip==NULL) return 1;
  if (nEntry<nCurrFile)
  {
    // We'll have to go through the zip file again to get to our entry
    nRet=unzGoToFirstFile(Zip); if (nRet!=UNZ_OK) return 1;
    nCurrFile=0;
  }

  // Now step through to the file we need
  while(nCurrFile<nEntry)
  {
    nRet=unzGoToNextFile(Zip); if (nRet!=UNZ_OK) return 1;
    nCurrFile++;
  }

  nRet=unzOpenCurrentFile(Zip); if (nRet!=UNZ_OK) return 1;

  nRet=unzReadCurrentFile(Zip,Dest,nLen);
  if (nRet>=0 && pnWrote!=NULL) *pnWrote=nRet; // Return how many bytes were copied

  nRet=unzCloseCurrentFile(Zip);
  if (nRet==UNZ_CRCERROR) return 2;
  if (nRet!=UNZ_OK) return 1;

  return 0;
}
