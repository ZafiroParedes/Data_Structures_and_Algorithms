// this is testlib.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string>
#include <vector>
#include "testlib.h"

using namespace std;

tester::tester(int c, char * * p, vector <string> & v): vs(v), vcs(dvcs), as(das), acs(dacs)
{ argc=c;
  argv=p;
  isvec=true;
  isstr=true;
  prepare(); }
  
tester::tester(int c, char * * p, vector <char *> & v): vs(dvs), vcs(v), as(das), acs(dacs)
{ argc=c;
  argv=p;
  isvec=true;
  isstr=false;
  prepare(); }

tester::tester(int c, char * * p, string * & a): vs(dvs), vcs(dvcs), as(a), acs(dacs)
{ argc=c;
  argv=p;
  isvec=false;
  isstr=true;
  prepare(); }

tester::tester(int c, char * * p, char * * & a) : vs(dvs), vcs(dvcs), as(das), acs(a)
{ argc=c;
  argv=p;
  isvec=false;
  isstr=false;
  prepare(); }

tester::~tester()
{ }

vector <string> tester::dvs(0);
vector <char *> tester::dvcs(0);
string * tester::das = NULL;
char * * tester::dacs = NULL;
 
void tester::prepare()
{ minwidth=0;
  maxwidth=0;
  bigcheck=true;
  frac=0.0;
  time1=0.0;
  time2=0.0;
  int seed=0, len=0;
  origs=NULL;
  unrandom=false;
  printthem=false;
  bool show=false;
  for (int i=1; i<argc; i+=1)
  { if (argv[i][0]=='p')
    { unrandom=true;
      frac=atof(argv[i]+1); }
    else if (argv[i][0]=='s')
    { seed=atol(argv[i]+1);
      show=true; }
    else if (argv[i][0]=='q')
    { bigcheck=false; }
    else if (argv[i][0]=='v')
    { printthem=true; }
    else if (len==0)
      len=atol(argv[i]);
    else if (minwidth==0)
      minwidth=atol(argv[i]);
    else if (maxwidth==0)
      maxwidth=atol(argv[i]); }
  if (len==0)
    len=1000000;
  if (minwidth==0)
    minwidth=10;
  if (maxwidth<minwidth)
    maxwidth=minwidth;
  randy = new char[maxwidth+1];
  randy[0]='A';
  for (int i=1; i<minwidth; i+=1)
    randy[i]='a';
  randy[minwidth]=0;
  if (seed==0)
  { srandomdev();
    seed=random();
    if (show)
      printf("seed = %d\n", seed); }
  srandom(seed);
  set_number(len);
  for (int i=0; i<len; i+=1)
    set_entry(i, make_random());
  if (unrandom)
  { int perms=(int)(frac*len/2);
    for (int i=0; i<perms; i+=1)
    { int p=random()%len;
      int q=random()%len;
      exchange(p, q); } }
  time1=getcputime(); }

void tester::set_number(int len)
{ length=len;
  if (bigcheck && origs==NULL)
    origs = new char * [length];
  if (isvec)
  { if (isstr)
      vs.resize(length);
    else
      vcs.resize(length); }
  else if (isstr)
    as = new string [length];
  else
    acs = new char * [length]; }

char * duplicate(const char * s)
{ int n=strlen(s);
  char * r = new char[n+1];
  for (int i=0; i<=n; i+=1)
    r[i]=s[i];
  return r; }

void tester::set_entry(int i, char * s)
{ if (isvec)
  { if (isstr)
      vs[i]=s;
    else
      vcs[i]=duplicate(s); }
  else if (isstr)
    as[i]=s;
  else
    acs[i]=duplicate(s);
  if (bigcheck && origs!=NULL)
    origs[i]=duplicate(s); }

const char * tester::get_entry(int i)
{ if (isvec)
  { if (isstr)
      return vs[i].c_str();
    else
      return vcs[i]; }
  else if (isstr)
    return as[i].c_str();
  else
    return acs[i]; }

bool tester::compare_entry(int i, char * s)
{ if (isvec)
  { if (isstr)
      return vs[i]==s;
    else
      return strcmp(vcs[i], s)==0; }
  else if (isstr)
    return as[i]==s;
  else
    return strcmp(acs[i], s)==0; }

void tester::exchange(int p, int q)
{ if (isvec)
  { if (isstr)
    { string t = vs[p]; vs[p]=vs[q]; vs[q]=t; }
    else
    { char * t = vcs[p]; vcs[p]=vcs[q]; vcs[q]=t; } }
  else if (isstr)
  { string t = as[p]; as[p]=as[q]; as[q]=t; }
  else
  { char * t = acs[p]; acs[p]=acs[q]; acs[q]=t; } }

int tester::get_number()
{ return length; }

double tester::how_long()
{ return time2-time1; }

char * tester::make_random()
{ if (unrandom)
    generate_rough();
  else
    generate_random();
  return randy; }

void tester::generate_random()
{ int len=random()%(maxwidth+1-minwidth)+minwidth;
  randy[0]=random()%26+'A';
  for (int i=1; i<len; i+=1)
    randy[i]=random()%26+'a';
  randy[len]=0; }

void tester::generate_rough()
{ int incr=random()%100;
  int pos=minwidth-1;
  while (pos>=0)
  { int c=randy[pos];
    c+=incr;
    if (c<='z')
    { randy[pos]=c;
      break; }
    else
    { c-='a';
      incr=c/26;
      c%=26;
      randy[pos]=c+'a';
      pos-=1; } }
  if (maxwidth<=minwidth)
    return;
  int extra = random()%(maxwidth-minwidth+1);
  for (int i=0; i<extra; i+=1)
    randy[minwidth+i]='a'+random()%26;
  randy[minwidth+extra]=0; }

static int special_compare(const void * a, const void * b)
{ return strcmp(* (const char * *)a, * (const char * *)b); }

bool tester::verify()
{ if (bigcheck)
  { qsort(origs, length, sizeof(char *), special_compare);
    for (int i=0; i<length; i+=1)
    { if (!compare_entry(i, origs[i]))
      { printf("Not correctly sorted: entry %d is %s, should be %s\n", i, get_entry(i), origs[i]);
        return false; } }
    return true; }
  else
  { const char * prev = get_entry(0);
    for (int i=1; i<length; i+=1)
    { const char * curr = get_entry(i);
      if (strcmp(prev, curr)>0)
      { printf("Not correctly sorted: entry %d (%s) > entry %d (%s)\n", i-1, prev, i, curr);
        return false; }
      prev=curr; }
    return true; } }

double tester::getcputime()
{ struct timeval tim;        
  struct rusage ru;        
  getrusage(RUSAGE_SELF, &ru);        
  tim=ru.ru_utime;        
  double t=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;        
  tim=ru.ru_stime;        
  t+=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;        
  return t; }        

void tester::printall()
{ for (int i=0; i<length; i+=1)
  { printf("%7d: %*s", i, maxwidth+2, get_entry(i));
    if (bigcheck && origs!=NULL)
      printf("  %s", origs[i]);
    printf("\n"); }
  printf("\n"); }

bool tester::finish()
{ time2 = getcputime();
  bool ok = verify();
  if (printthem)
    printall();
  if (!ok)
  { fprintf(stderr, "Sorting failed\n");
    return false; }
  double t=time2-time1;
  double nlogn=length*log(length)/log(2);
  printf("%10d items sorted in %9.4f seconds, nlogn=%.4e, ratio=%.3e\n", length, t, nlogn, nlogn/t);
  return true; }

