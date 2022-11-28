#include<iostream>
#include<iomanip>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<fstream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

 struct sinhvien
{
	string hoten;
	int tuoi;
	float diem;
};
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE), color);	
}
int gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE), coord);			
}
void docfile( sinhvien sv[],int &index)
{
	fstream filein;
	filein.open("sinhvien.txt", ios_base::in);
	sinhvien a;
	while(true)
	{
	getline(filein, a.hoten, ',');
	filein>>a.tuoi;
	filein.ignore();
	filein>> a.diem;
	if(filein.eof() == true) break;
	filein.ignore();
	 sv[index++] = a ;
	
	}
	filein.close();
}

vector<string> chuanhoa(string s)
{
	stringstream ss(s); vector<string> v;
	string token;
	while(ss >> token )
	{
		v.push_back(token);
	}
	return v;
}
bool cmp(sinhvien a, sinhvien b)
{
	vector<string> v1= chuanhoa(a.hoten), v2=chuanhoa(b.hoten);
	if(v1.back() != v2.back()) return v1.back() < v2.back();
	int len1 = v1.size(), len2 = v2.size();
	for(int i=0;i< min(len1, len2);i++)
	{
		if(v1[i] != v2[i])
		return v1[i] < v2[i];
	}
	return len1 < len2;
}
void sxten(sinhvien sv[],int index)
{
	sort(sv,sv + index,cmp);
}
void nhapsv(sinhvien sv[],int &index)
{
	textcolor(13);
	cout<<" \n(1) Moi Ban Nhap Danh Sach Sinh Vien! \n\n";
	cin.ignore();
	cout<<"      (?) Nhap Ten Sinh Vien: ";
	getline(cin, sv[index].hoten);
	fflush(stdin);
	cout<<"      (?) Nhap Tuoi Sinh Vien: ";
	cin>>sv[index].tuoi;
	cout<<"      (?) Nhap Diem Sinh Vien: ";
	cin>>sv[index].diem;
	index++;
}
void xuatsv(sinhvien sv[],int index)
{
	
		cout<<endl<<endl;
		cout<<"               +------+------------------------+-----------+------------+\n";
		cout<<"               |  STT |      HO va TEN         |    TUOI   |    DIEM    |\n";
		cout<<"               +------+------------------------+-----------+------------+\n";
		for(int i=0;i<index;i++)
				{
					cout<<"               |"<<setw(3)<<i+1<<"   | ";
					cout<<setw(14)<<sv[i].hoten<<"         | "<<setw(6)<<sv[i].tuoi<<"    | "<<setw(6)<<sv[i].diem<<"     |\n";
				}
		cout<<"               +------+------------------------+-----------+------------+\n";
}

int xoa1sv(sinhvien sv[],int p, int index)
	{
		int cout = 0;
		for(int i= p-1;i<index-1;i++)
		{
			sv[i] = sv[i + 1];
		}
		sv[index-1].hoten ="";
		sv[index-1].tuoi = 0;
		sv[index-1].diem = 0;
		cout++;
		return cout;
	}
void xoa(sinhvien sv[], int &index)
{
	textcolor(7);
	int p;
	cout<<"\n   (2) Xoa!\n";
	cout<<"          (?) Ban Hay Quan Sat!";
	xuatsv(sv,index);
	cout<<"          (?) Ban Muon Xoa Sinh Vien Co STT: ";
	cin>>p;
	int cout = xoa1sv(sv,p,index);
	int val= index - cout;
	sinhvien ls[val];	
	for(int i=0;i<val;i++)
	ls[i]=sv[i];
	xuatsv(ls,val);
	index--;
}
void capnhat(sinhvien sv[], int index)
{
	textcolor(12);
	int p;
	cout<<"\n   (3) Cap Nhat!\n";
	cout<<"          (?) Ban Hay Quan Sat!";
	xuatsv(sv,index);
	cout<<"          (?) Ban Muon Cap Nhat Sinh Vien Co STT: ";
	cin>>p;
	cin.ignore();
	cout<<"              (1) Moi Ban Nhap Ten: ";
	getline(cin,sv[p-1].hoten);
	fflush(stdin);
	cout<<"              (2) Moi Ban Nhap Tuoi: ";
	cin>>sv[p-1].tuoi;
	cout<<"              (3) Moi Ban Nhap Diem: ";
	cin>>sv[p-1].diem;
	cout<<"          (?) Da Cap Nhat Xong!\n";
	xuatsv(sv,index);
}



void timkiem(sinhvien sv[], int index)
{
	textcolor(7);
	string s;
	cout<<"\n   (7) Tim Kiem!\n";
	cout<<"          (?) Nhap Tu Khoa De Tim: ";
	cin>>s;
	bool found = false;
	int n=0;
	sinhvien *v= new sinhvien[100];
	for(int i=0;i<index;i++)
	{
		if(sv[i].hoten.find(s) != string::npos)// npos là giá tri max cua kieu du lieu size t
		{	
			v[n++]=sv[i];
			found = true;
			
		}				
	}
	if(!found) cout<<" \n           (?) Khong Tim Thay Sinh Vien!"<<endl;
	else xuatsv(v,n);
	
}
void sapxep(sinhvien sv[], int index)
{
	textcolor(5);
	cout<<"\n   (6) Sap Xep Tang Dan!\n";
	cout<<"          \n(?) Sap Xep Theo Diem!";
	sinhvien temp;
	for (int i=0;i<index;i++)
		for(int j=i+1;j<index;j++)
		{
			if(sv[i].diem>sv[j].diem)
			{
			    temp = sv[i];
				sv[i] = sv[j];
				sv[j] = temp; 
			}
		}
	
	xuatsv(sv,index);	
	cout<<"          \n(?) Sap Xep Theo Ho Ten!";
	 sxten(sv,index);
	 xuatsv(sv,index);
	 

}
void thongke(sinhvien sv[], int index)
{
	textcolor(14);
	cout<<"\n   (7) Thong Ke!\n";
	float diem=0, max=sv[0].diem;
	int n = 0,x = 0;
		for(int i=0; i<index;i++) 
		{
			diem = diem+sv[i].diem;
			if(sv[i].diem >= 5){ n++ ;}
		//	if(max < sv[i].diem)
    	//	{
    	//	x++;
		//	max=sv[i].diem;
    		
		//	}
		}
	for (int j = 0; j < index-1; ++j)
		if (max < sv[j+1].diem)
			{
				max = sv[j+1].diem;
				x = j+1;

			}
	int tb= n*100/index;
	cout<<"\n          (!) Diem Trung Binh Ca Lop La: "<<diem/index<<endl;
	cout<<"\n          (!) Ti Le Sinh Vien Tren Trung Binh La: "<<tb<<"%"<<endl;
	cout<<"\n          (!) Sinh Vien Co Diem Cao Nhat La: "<<sv[x].hoten<<". Dat Duoc Diem: "<<max<<endl;	
}

void saoluu( sinhvien sv[],int index)
{
	cout<<"\n   (8) Sao Luu!\n";
	fstream outfile;
	outfile.open("sinhvien.txt", ios_base::out);
	for(int i=0;i<index;i++)
	{
		outfile<<sv[i].hoten<<","<<sv[i].tuoi<<","<<sv[i].diem;
		outfile<<endl;
	}
	outfile.close();
	
	textcolor(6);
	int x=10, y=18;
	gotoxy(x-6,y); cout<<"Start";
	for(int i=0; i<33;i++)
	{
		gotoxy(x+ i,y); cout<<"-";
		Sleep(100);
    }
   		 Sleep(300);
        gotoxy(x+34,y); cout<<"Done\n\n";
        Sleep(500);
	cout<<"          (?) Tien Hanh Sao Luu Thanh Cong!\n";
}
void menu(sinhvien sv[], int index)
{
	int choice;
	do{
		textcolor(11);
		system("cls");
		cout<<"=========================================="<<"\n";
		cout<<"================= MENU ==================="<<"\n";
		cout<<"=========================================="<<"\n";
		cout<<" 1. Them  "<<"\n";
		cout<<" 2. Xoa  "<<"\n";
		cout<<" 3. Cap nhat "<<"\n";
		cout<<" 4. Quan sat "<<"\n";
		cout<<" 5. Tim Kiem"<<"\n";
		cout<<" 6. Sap Xep"<<"\n";
		cout<<" 7. Thong Ke"<<"\n"; 
		cout<<" 8. Sao luu"<<"\n"; 
		cout<<" 9. Thoat"<<"\n"; 
	cout<<"\n(?) Moi Ban Chon: ";
	cin>>choice;
	switch (choice)
	{
		case 1: nhapsv(sv,index); system("pause"); break;
		case 2: xoa(sv,index);system("pause"); break;
		case 3: capnhat(sv,index);system("pause"); break;
		case 4: textcolor(3); cout<<"\n   (4) Quan Sat!"; xuatsv(sv,index);system("pause"); break;
		case 5: timkiem(sv,index);system("pause"); break;
		case 6: sapxep(sv,index);system("pause"); break;
		case 7: thongke(sv,index);system("pause"); break;
		case 8: saoluu(sv,index);system("pause"); break;
		case 9: exit(0); break;
		default:cout<<"Khong hop le";
			
	}
	}while(choice !=0);
}
int main()
{
	sinhvien sv[100];
	int index=0;
	docfile(sv,index);
	menu(sv,index);
	return 0;
}


