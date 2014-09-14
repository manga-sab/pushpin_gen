#include<highgui.h>
#include<cv.h>
using namespace std;
using namespace cv;
Vec3b colour[7];
Vec3b find_similar(Vec3b a)
{
long int dist,min_index=0,min_dist=32767;
for (int i=0;i<7;i++)
{
dist = sqrt(pow((colour[i][0]-a[0]),2) + pow((colour[i][1]-a[1]),2) + pow((colour[i][2]-a[2]),2));
if (dist<=min_dist)
{
min_dist=dist;
min_index=i;
}
}
return colour[min_index];
}
char colour_finder(Vec3b a)
{
if (a[0]==255)
{
if (a[1]==255)
return 'w';
else
return 'b';
}
else if (a[1]==255)
{
if (a[2]==255)
return 'y';
else
return 'g';
}
else
{
if (a[2]==255)
{
if (a[1]==140)
return 'o';
else
return 'r';
}
else
return 'n';
}

}
int main(int argc,char **argv)
{
colour[0]=Vec3b(0,0,0);
colour[1]=Vec3b(240,100,100);
colour[2]=Vec3b(120,100,100);
colour[3]=Vec3b(180,100,100);
colour[4]=Vec3b(0,100,100);
colour[5]=Vec3b(0,0,100);
colour[6]=Vec3b(0,140,255);

int width,height;

cout<<"Please enter the output file width"<<endl;
cin>>width;
cout<<"Please enter the output file height"<<endl;
cin>>height;

FILE *fp=fopen("output1.csv","w");
Mat img=imread(argv[1]);
resize(img,img,Size(),(double)width/img.cols,(double)height/img.rows);
imshow("orig",img);

for (int i=0;i<height;i++)
{
for (int j=0;j<width;j++)
{
img.at<Vec3b>(i,j)=find_similar(img.at<Vec3b>(i,j));
fprintf(fp,"%c ",colour_finder(img.at<Vec3b>(i,j)));
}
fprintf(fp,"\n");
}
imshow("new",img);
cvWaitKey(0);
}
