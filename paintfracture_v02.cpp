#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <fstream>

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <list>
#include <sstream>
#include <time.h>
#include <algorithm>


//#include "Vector3f.h"

//#include "stdafx.h"
//#include "Point3.h"

// random generator function:
ptrdiff_t myrandom (ptrdiff_t i) { return rand()%i;}

// pointer object to it:
ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom;

using namespace std;

class Point3
	{
	public:
		union
		{
			struct
			{
				int x, y, z;
			};
			int val[3];
		};
		
		Point3();
		Point3(int x, int y, int z);
		inline bool operator == ( const Point3& r ) const
		{
			return ( x == r.x && y == r.y && z == r.z );
		}
		
		inline Point3& operator = ( const Point3& rkVector )
		{
			x = rkVector.x;
			y = rkVector.y;
			z = rkVector.z;
			
			return *this;
		}
		
		inline bool operator != ( const Point3& rkVector ) const
		{
			return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
		}
		
		// arithmetic operations
		inline Point3 operator * ( const int rkVector ) const
		{
			Point3 kSum;
			
			kSum.x = x * rkVector;
			kSum.y = y * rkVector;
			kSum.z = z * rkVector;
			
			return kSum;
		}
		
		// arithmetic operations
		inline Point3 operator + ( const Point3& rkVector ) const
		{
			Point3 kSum;
			
			kSum.x = x + rkVector.x;
			kSum.y = y + rkVector.y;
			kSum.z = z + rkVector.z;
			
			return kSum;
		}
		
		inline Point3 operator - ( const Point3& rkVector ) const
		{
			Point3 kDiff;
			
			kDiff.x = x - rkVector.x;
			kDiff.y = y - rkVector.y;
			kDiff.z = z - rkVector.z;
			
			return kDiff;
		}
		
		// arithmetic updates
		inline Point3& operator += ( const Point3& rkVector )
		{
			x += rkVector.x;
			y += rkVector.y;
			z += rkVector.z;
			
			return *this;
		}
		
		inline Point3& operator -= ( const Point3& rkVector )
		{
			x -= rkVector.x;
			y -= rkVector.y;
			z -= rkVector.z;
			
			return *this;
		}
		
		inline bool operator< (const Point3 &b) const
		{
			if (x < b.x)
				return true;
			
			if (b.x < x)
				return false;
			
			// now, we know that a.x == b.x
			// compare on y
			
			if (y < b.y)
				return true;
			
			if (b.y < y)
				return false;
			
			// now, we know that (a.x == b.x) && (a.y == b.y)
			// compare on y
			
			if (z < b.z)
				return true;
			
			return false;
		}
	};

Point3::Point3()
{
}

Point3::Point3(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}





int findids(int key,map<int,int> ids){
	return ids[key];
}

int findkey(int id,map<int,int> ids){
	int key=-1;
	
	std::map<int,int>::const_iterator it;
	for(it=ids.begin();it!=ids.end();++it){
		if(it->second==id){
			key=it->first;
			break;
		}
	}
	
	return key;
}

int pushback_id(int key,int id,map<int,int> *ids){
	std::map<int,int>::const_iterator it;
	map<int,int> &tids=*ids;
	//printf("test\n");
	//for(it=tids.begin();it!=tids.end();++it)printf("%d",it->second);
	//printf("\n");
	for(it=tids.begin();it!=tids.end();it++){
		if(it->second==id){
			//printf("nindex=%d id=%d sec=%d\n",it->first,id,it->second);
			return (it->first);
		}	
	}
	//printf("size=%d\n",tids.size());
	//printf("index=%d id=%d\n",tids.size(),id);
	tids.insert(map<int,int>::value_type(tids.size(),id));
	//printf("in_pushback:%d\n",tids.size()-1);
	return (tids.size()-1);
	
}

int max(int a,int b){
	if(a>b)return a;
	else return b;
}

int clamp(int v,int min,int max){
	if(v<=min)return min;
	else if(v>=max)return max;
	else return v;
}



int chkneighbor(Point3 index,vector<int> *domain,vector<float> *sdfdata,vector<int> *flag,int resx,int resy,int resz,int cnt){
	
	/*vector<int> *testarray=flag;
	 for (int i=0;i<24;i++) {
	 printf("testarray[%d]=%d\n",i,(*testarray)[i]);
	 }*/
	int dindex=index.x+resy*index.y+pow(resz,2)*index.z;
	int cindex;
	//printf("chk....dindex=%d\n",dindex);
	
	int fillflag=0;
	
	//if(rnd>5){
	float tempmax=0;
	float delta=0;
	int findex=0;
	for(int xo=-1;xo<=1;xo++){
		for(int yo=-1;yo<=1;yo++){
			for(int zo=-1;zo<=1;zo++){				
				if((xo==-1&&yo==-1&&zo==-1)||(xo==1&&yo==-1&&zo==-1)||(xo==1&&yo==-1&&zo==1)||(xo==-1&&yo==-1&&zo==1)||(xo==-1&&yo==1&&zo==-1)||(xo==1&&yo==1&&zo==-1)||(xo==-1&&yo==1&&zo==1)||(xo==1&&yo==1&&zo==1)){;}
				else{
					cindex=clamp(index.x+xo,0,resx-1)+resy*clamp(index.y+yo,0,resy-1)+pow(resz,2)*clamp(index.z+zo,0,resz-1);
					//srand(cindex*10000);
					//int rnd=(rand()%10);
					//printf("rnd=%d\n",rnd);
					delta=-1*((*sdfdata)[cindex]-(*sdfdata)[dindex]);
					//if(delta>=0)(*flag)[cindex]=cnt;
					//if(delta>tempmax){
					//if(yo==0)printf("delta=%f\n",delta);
						//tempmax=delta;
						findex=cindex;						
					//}
					if((*domain)[findex]==0 && (*domain)[dindex]!=0 && delta>0){
						(*domain)[findex]=(*domain)[dindex];
						(*flag)[findex]=cnt;
						fillflag=1;
					}
					//if((*domain)[cindex]==0 && (*domain)[dindex]!=0 && (*flag)[dindex]==0 && sdf[dindex]<0){

				}
			}
		}
	}



			
			//(*flag)[dindex]=cnt;
			//printf("in_chk\n");

	//printf("delta=%f\n",delta);
	//printf("fidnex=%d\n",findex);

	//}
	
	return fillflag;
}


vector<float> splitf(string str, string delim)
{
    vector<float> result;
    int cutAt;
    while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
        if(cutAt > 0)
        {
			//printf("cutAt=%d ",cutAt);
            result.push_back(atof(str.substr(0, cutAt).c_str()));
			//printf("id=%f ",atof(str.substr(0, cutAt).c_str()));
        }
        str = str.substr(cutAt + 1);
		
    }
    if(str.length() > 0)
    {
        result.push_back(atof(str.c_str()));
    }
	return result;
}

vector<int> split(string str, string delim)
{
    vector<int> result;
    int cutAt;
    while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
        if(cutAt > 0)
        {
			//printf("cutAt=%d ",cutAt);
            result.push_back(atoi(str.substr(0, cutAt).c_str()));
			//printf("id=%d ",atoi(str.substr(0, cutAt).c_str()));
        }
        str = str.substr(cutAt + 1);

    }
    if(str.length() > 0)
    {
        result.push_back(atoi(str.c_str()));
    }
	return result;
}

vector<string> str_split(string str, string delim)
{
    vector<string> result;
    int cutAt;
    while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
        if(cutAt > 0)
        {
            result.push_back(str.substr(0, cutAt).c_str());
        }
        str = str.substr(cutAt + 1);
    }
    if(str.length() > 0)
    {
        result.push_back(str.c_str());
    }
	return result;
}

vector<int> arrayconv(string str, string delim)
{
    vector<int> result;
	
}

int main(int argc, char *argv[])
{
	int m, n;
	map<int, int> ids;
	set<int> idset;


	//std::cout << "m = ";
	//std::cin >> m;
	//std::cout << "N(ID Num) = ";
	//std::cin >> n;
	
	FILE *fp;
	fp = fopen(argv[1], "r");
	string str;
	char t_char[5];
	char chr[20];
	//int temp=findkey(m,ids);
	
	//printf("id=%d\n",temp);
	
	//int domain[64]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
	//int	  flag[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	//FileOpen
	ifstream ifs(argv[1]);
	string buf;
	int nprims=0,indexSDF,indexVolume,indexNPrims,indexNPAttr,resx,resy,resz,transflag=0;
	int indexNPoints;
	vector<int> resdata,smokedata;
	vector<float> sdfdata;
	//vector<int> sdfdata;
	
	int get_ch;
	fpos_t position;
	int volflag=0,sdfflag=0,vol_id,size;
	float sdf_id;
	//char cresx[10],cresy[10],cresz[10];
	//while((get_ch=fgetc(fp))!=EOF){
		//sprintf(chr,"%c",get_ch);
		//printf("%s",chr);
	//}
	while (fscanf(fp,"%s",chr)!=EOF) {
		//printf("%s\n",chr);
		if(!strcmp("Volume",chr)){
			fscanf(fp,"%d",&vol_id);
			if(vol_id==0)volflag=1;
			else if(vol_id==1)sdfflag=1;
		}
		if(volflag){
			if(!strcmp("-2",chr)){
				fscanf(fp,"%d%d%d",&resx,&resy,&resz);
			}
			size=resx*resy*resz;
			
			int temp1,temp2;
			if(!strcmp("smoke",chr)){
				fscanf(fp,"%d%d",&temp1,&temp2);
				printf("smoke in\n");
				for(int i=0;i<size;i++){
					int temp_id;
					fscanf(fp,"%d",&temp_id);
					smokedata.push_back(temp_id);
				}
			}			
			if(!strcmp("[1]",chr)){
				volflag=0;
			}
			
		}
		if(sdfflag){
			if(!strcmp("smoke",chr)){
				int temp1,temp2;
				fscanf(fp,"%d%d",&temp1,&temp2);
				printf("sdf in\n");
				for(int i=0;i<size;i++){
					fscanf(fp,"%f",&sdf_id);
					sdfdata.push_back(sdf_id);
				}
				break;
			}
		}
	}
	fclose(fp);
	printf("x=%d,y=%d,z=%d\n",resx,resy,resz);

	
	printf("file:%s\n",argv[1]);
	int smokedatasize=smokedata.size();//sizeof(smokedata)/sizeof(int);
	int len=cbrt(smokedatasize);
	vector<int> flag(smokedata.size());

	vector<int>::iterator itersdf=flag.begin();	
	while(itersdf!=flag.end()){
		*itersdf=-1;
		++itersdf;
	}
	vector<int> rndindex;
	vector<int>::iterator iter_rndindex;
	
	for(int i=0;i<smokedatasize;i++)rndindex.push_back(i);
	//random_shuffle ( rndindex.begin(), rndindex.end(),p_myrandom );
	
	//Point3 index=0;
	
	//Point3 cpt=Point3(1,1,1);
	int fillflag=0;
	//for(int i=0;i<8;i++){
	int cnt=0;
	int tempcnt=0;
	while(1){
		for (int z=0;z<resz;z++) {
			for(int y=0;y<resy;y++){
				for(int x=0;x<resz;x++){
					//index=x+2*y+2*2*z;
					int dindex=x+resy*y+pow(resz,2)*z;
					int rindex=rndindex[dindex];
					//printf("rindex=%d\n",rindex);
					//printf("resx=%d,resy=%d,resz=%d\n",resx,resy,resz);
					int rx,ry,rz;
					rz=rindex/(pow(resz,2));
					ry=(rindex-rz*pow(resz,2))/resy;
					rx=rindex-(ry*resy+rz*pow(resz,2));
					//printf("rx=%d,ry=%d,rz=%d\n",rx,ry,rz);
					
					//srand(dindex*0.1);
					//int rnd=(rand()%10);
					//printf("rnd=%d\n",rnd);
					if(sdfdata[rindex]<0 && flag[rindex]==cnt-1 ){
						//if(rnd>5)
							tempcnt=chkneighbor(Point3(rx,ry,rz),&smokedata,&sdfdata,&flag,resx,resy,resz,cnt );
						//else tempcnt=1;
						fillflag=fillflag+tempcnt;
					}
					//sprintf(t_char,"%d ",domain[index]);
					//sr+=t_char;
					//cnt++;
				}
			}
		}
		cnt++;
		if(fillflag==0)break;
		fillflag=0;
		/*vector<int>::iterator iter=flag.begin();		
		while(iter!=flag.end()){
			*iter=0;
			++iter;
		}*/
	}
	

	//fprintf(fp, "%s \n",str.c_str());
	//fclose(fp);
	//int domain[8]={4,2,3,6,3,2,4,6};

	for(int i=0;i<smokedatasize;i++){
		
		//printf("smokedata[%d]=%d\n",i,smokedata[i]);
		if(smokedata[i]!=0)idset.insert(smokedata[i]);
	}
	//idset.erase(3);
	int idsize=idset.size();
	printf("size=%d\n",idset.size());

	std::vector<std::vector<int> > vvi(idsize, std::vector<int>(smokedatasize));
	//std::vector<std::vector<int> > vvi;
	
	//vvi.resize(8);
	int id=0;
	int j,tempid;
	
	
	for (int i = 0; i < smokedatasize; i++){
		//printf("domain[%d]=%d\n",i,smokedata[i]);
		tempid=smokedata[i];
		std::map<int,int>::const_iterator it;
		if(tempid!=0){
		int index=pushback_id(i,tempid,&ids);
		//printf("next_index=%d\n",index);
		//for(it=ids.begin();it!=ids.end();++it)printf("%d",it->second);
		//printf("\n");
		vvi[index][i]=tempid;
		}
		//ids.insert(map<int,int>::value_type(j,id))
	}

	//std::map<int,int>::const_iterator it;
	//for(it=ids.begin();it!=ids.end();++it){	
	//	printf("key=%d,value=%d\n",it->first,it->second);
	//}
	/*for (int i = 0; i < idsize; i++) {
		std::copy(vvi[i].begin(), vvi[i].end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}*/
	//printf("midpoint\n");
	//File write
	ifstream ifs1(argv[1]);
	ifs1.seekg(0,ios::beg);
	//ofstream outfile("myvol.geo");
	ofstream outfile(argv[2]);
	
	string cstr;
	bool wflag=1;
	char tempstring[30];
	char nvolume[10];
	vector<string> splitVol;
	vector<string>::iterator it;
	vector<int>::iterator intit;
	
	while(ifs1 && getline(ifs1,buf)){
		string outstr;
		wflag=1;
		
		//printf("writing..\n");
		//NPrims
		indexNPrims=buf.find("NPrims");
		//NPointAttrib
		indexNPAttr=buf.find("NPointAttrib");
	 
		//Volume
		indexVolume=buf.find("Volume 0");
		indexSDF=buf.find("Volume 1");
		
	 
		if(indexNPrims!=-1){
			string nprims_str=buf.substr(indexNPrims+7);
			nprims=atoi(nprims_str.c_str());
			printf("nprims:%i\n",nprims);
			
			sprintf(tempstring,"NPoints %d NPrims %d",idsize,idsize);
			buf=string(tempstring);
		}
		else if(indexNPAttr!=-1){
			transflag=1;
			//buf="";
		}
		else if(transflag==1){
			//printf("trans:%s\n",buf.c_str());
			for(int i=0;i<idsize;i++){
				outfile.write(buf.c_str(),buf.size());
				outfile.write("\n",1);
				//printf("intrans\n");
			}
			transflag=2;
			buf="";
			//printf("bufsize=%d\n",buf.size());
		}
		else if(transflag==2){
			buf="";
			transflag=0;
		}
		else if(indexVolume!=-1){
			for(int i=0;i<idsize;i++){
				sprintf(nvolume,"Volume %d ",i);

				
				int smokeindex=buf.find("smoke");
				string voldescript=buf.substr(0,smokeindex+9);
				cout<<voldescript<<endl;
				splitVol=str_split(voldescript," ");
				
				string concate;
				for (it=splitVol.begin()+2;it<splitVol.end();it++) {
					concate+=(*it+" ");
				}
				
				cstr=string(nvolume)+concate;
				outfile.write(cstr.c_str(),cstr.size());
				//printf("debug:%s\n",cstr.c_str());

				for (intit=vvi[i].begin();intit<vvi[i].end();intit++){
					std::ostringstream ss;
					ss<<*intit;
					string id=ss.str()+" ";
					//cout<<id;
					outfile.write(id.c_str(),id.size());

				}
				wflag=0;
				outfile.write("[0]",3);
				//cout<<concate;
				//cout<<endl;
				outfile.write("\n",1);
			}
			buf="";
		}
		else if(indexSDF!=-1)buf="";
		else;
		
		outstr=buf;
		
		if(outstr.size() && wflag){
			//printf("last:%s\n",outstr.c_str());
			outfile.write(outstr.c_str(),outstr.size());
			outfile.write("\n",1);
		}
	}
	
	
}