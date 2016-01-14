#include "stdafx.h"
#include "MyFunctions.h"


using namespace std;






//////////////////////////////////////////////////////////////////////////
double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize];//����� ������� � �������, ��� ������� SP,SM ��� SZ,����� ����, ����� �������
double VmatrixInside[MatrixSize][MatrixSize];//���������� ��� ���������� �����������
double Energie[MatrixSize]; //������� ���������
inter curInter [N][maxIntElem]; //������ ���������� �������������
int interAmount[N];// ���-�� ��-��� � ������ ���������

vector<state> vIn[Namount],vOut1[Namount],vOut2[Namount]; //������� ��������-���������� �� ������� ���� ��� ������� ������ ��� ��������, �� ��������� ���� - ��������
vector<state> vOutTemp1,vOutTemp2;//������������� �������
vector<state> vtemp;
vector<state> temp,temp2,tempvec,tempvec2;
unordered_map<state, double> map_temp, map_temp2, map_tempvec, map_tempvec2;
state init;
//////////////////////////////////////////////////////////////////////////

std::size_t std::hash<state>::operator()(const state& k) const{
	//return (std::hash<string>()(out.str()));
	size_t res=0,factor = 1;
	for (int i = 0; i < N; i++){
		res += k.states[i] * factor;
		if(i!=N-1)factor *= 100;
	}
	res += k.coeff[0] * 10 * factor + k.coeff[1] * 100 * factor + k.coeff[2] * 100 * factor ;
	return res;
}

//����������� 0- (0,0); ����� ������ ������� �������
void returnV(inter curInter[][maxIntElem],int interAmount[],int interN,int n1,int n2,int dx,int dy) //n1,n2 - ���������� ������ ��������������� �������, dir -����������� �� ������� ������� �� �������
{

	/*switch(dir)
	{
	case 0: dx=1;   dy=0;  break;
	case 1: dx=1;   dy=1;  break;
	case 2: dx=0;   dy=1;  break;
	case 3: dx=-1;  dy=1;  break;
	case 4: dx=-1;  dy=0;  break;
	case 5: dx=-1;  dy=-1; break;
	case 6: dx=0;   dy=-1; break;
	case 7: dx=1;   dy=-1; break;
	}*/
	int q=-1;
	if((dx==1)&&(dy==0))// �� ����������� �������
	{
		q++;
		curInter[interN][q].Jtype=0;
		curInter[interN][q].n1=n1; curInter[interN][q].n2=n2;
		curInter[interN][q].v1=2;  curInter[interN][q].v2=5;

		q++;
		curInter[interN][q].Jtype=1;
		curInter[interN][q].n1=n1; curInter[interN][q].n2=n2;
		curInter[interN][q].v1=1;  curInter[interN][q].v2=5;

		q++;
		curInter[interN][q].Jtype=1;
		curInter[interN][q].n1=n1; curInter[interN][q].n2=n2;
		curInter[interN][q].v1=3;  curInter[interN][q].v2=5;

		q++;
		curInter[interN][q].Jtype=1;
		curInter[interN][q].n1=n1; curInter[interN][q].n2=n2;
		curInter[interN][q].v1=2;  curInter[interN][q].v2=0;
		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 2;  curInter[interN][q].v2 = 4;
	}//first ok 6

	if((dx==1)&&(dy==1)) //�� ��������� ������ �����
	{
		q++;
		curInter[interN][q].Jtype = 0;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 1;  curInter[interN][q].v2 = 4;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 1;  curInter[interN][q].v2 = 5;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 1;  curInter[interN][q].v2 = 3;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 0;  curInter[interN][q].v2 = 4;
		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 2;  curInter[interN][q].v2 = 4;
	}//first ok 6

	if((dx==0)&&(dy==1))//������ �����
	{
		q++;
		curInter[interN][q].Jtype = 0;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 0;  curInter[interN][q].v2 = 3;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 0;  curInter[interN][q].v2 = 2;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 0;  curInter[interN][q].v2 = 4;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 1;  curInter[interN][q].v2 = 3;
		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 5;  curInter[interN][q].v2 = 3;
	}//first ok 6
	
	if((dx==-1)&&(dy==0))//������ �����
	{
		q++;
		curInter[interN][q].Jtype = 0;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 5;  curInter[interN][q].v2 = 2;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 5;  curInter[interN][q].v2 = 1;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 5;  curInter[interN][q].v2 = 3;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 0;  curInter[interN][q].v2 = 2;
		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 4;  curInter[interN][q].v2 = 2;
	}//first �� 6 
	if((dx==-1)&&(dy==-1)) //�� ��������� ����� ����
	{
		q++;
		curInter[interN][q].Jtype = 0;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 4;  curInter[interN][q].v2 = 1;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 4;  curInter[interN][q].v2 = 0;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 4;  curInter[interN][q].v2 = 2;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 3;  curInter[interN][q].v2 = 1;
		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 5;  curInter[interN][q].v2 = 1;
	}//first �� 6
	if((dx==0)&&(dy==-1))//������ ����
	{
		q++;
		curInter[interN][q].Jtype = 0;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 3;  curInter[interN][q].v2 = 0;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 3;  curInter[interN][q].v2 = 1;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 3;  curInter[interN][q].v2 = 5;

		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 2;  curInter[interN][q].v2 = 0;
		q++;
		curInter[interN][q].Jtype = 1;
		curInter[interN][q].n1 = n1; curInter[interN][q].n2 = n2;
		curInter[interN][q].v1 = 4;  curInter[interN][q].v2 = 0;
	}//��

	interAmount[interN]=q+1;

}


void generate_all_Jfactors(int n,int **Jfactors)
{
	int temp;
	int cur_num=0;
	int *curJfac;
	for(int i=0;i<(n+1)*(n+1)*(n+1);i++)
	{
		temp=i;
		curJfac=new int[3];
		for(int j=0;j<3;j++)
		{
			curJfac[j]=temp%(n+1);
			temp/=(n+1);
		}
		if(curJfac[0]+curJfac[1]+curJfac[2]==n)
		{
			Jfactors[cur_num][0]=curJfac[0];
			Jfactors[cur_num][1]=curJfac[1];
			Jfactors[cur_num][2]=curJfac[2];
			cur_num++;
		}

	}
}

void generate_all_Jstrings(int n,int **Jfactors,string *strarr)
{
	bool first;
	string js[3];
	js[0]="J1^";
	js[1]="J2^";
	js[2]="(J2-0.5*J1)^";
	ostringstream out;
	for(int i=0;i<(n+2)*(n+1)/2;i++)
	{
		first=true;
		for(int j=0;j<3;j++)
		{
			if(Jfactors[i][j]!=0)
			{
				out.str("");
				if(first)
				{
					first=false;
					out<<Jfactors[i][j];
					strarr[i]=js[j]+out.str();
				}
				else
				{
					out<<Jfactors[i][j];
					strarr[i]+="*"+js[j]+out.str();
				}
			}
		}
	}
}

void collect(vector<state> &outvec,vector<state> &invec)
{
	int index=0;
	sort(invec.begin(),invec.end());
	outvec.push_back(invec[0]);
	for(unsigned int i=1;i<invec.size();i++)
	{
		if(invec[i]==outvec[index])
		{
			outvec[index].factor+=invec[i].factor;
		}
		else
		{
			if(abs(outvec[index].factor)<=0.000000000000001)
			{
				outvec.pop_back();
				--index;
			}
			++index;
			outvec.push_back(invec[i]);
		}
	}
}


void add_state_to_map(unordered_map<state, double> &cur_set, const state s)
{
	std::unordered_map<state, double>::iterator it = cur_set.find(s);
	if (it != cur_set.end()) it->second += s.factor; //add value to existed element
	else cur_set.insert({ s, s.factor }); //add new element;

}

/* #1 */void act(vector<state> &inv, vector<state> &outv, double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize], int interNumber)
{
	state tempst;
	int second_ort;
	//bool flag;
	temp2.clear();
	double curE,E0;
	E0=Energie[0]*N;

	vector<state>::iterator it;
	for(unsigned int inSt=0;inSt<inv.size();inSt++)
	{
		for(int i=0;i<interAmount[interNumber];i++) //���������� ��� ��-�� ��������������
		{
			//temp2.clear();
			//�-�������
			for(int ort=0;ort<3;ort++)
			{
				temp.clear();//������� ��������� ������ ���������, ����� ��� y � z ���������
				for (int j = 0; j<MatrixSize; j++)//��������� ��������� ����������� 1�� �����-
				{
					if(Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j]!=0)
					{
						//��� 1�� ������� ��� �����, ������ ���� ��������

						if(ort==1||ort==0)//�-����� �������, �� ���� �������� �� -1, ������ 1 ���
							tempst.factor=inv[inSt].factor*0.5*Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j];
						else
							tempst.factor=inv[inSt].factor*Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j];
						//�������� ������ ���������, ��� ��� �� ����� ����� ����� ��������
						for(int oldst=0;oldst<N;oldst++)
							tempst.states[oldst]=inv[inSt].states[oldst];

						//������ ���������
						tempst.states[curInter[interNumber][i].n1]=j;

						tempst.coeff[0]=inv[inSt].coeff[0];
						tempst.coeff[1]=inv[inSt].coeff[1];
						tempst.coeff[2]=inv[inSt].coeff[2];
						//������ ��� �������� ������ ������ ��������!!!
						tempst.coeff[curInter[interNumber][i].Jtype]++;

						temp.push_back(tempst);
					}
				}
				switch(ort)
				{
				case 0: second_ort=1; break;
				case 1: second_ort=0; break;
				case 2: second_ort=2; break;
				}
				for(int k=0;k<temp.size();k++) //��������� �� ���������� ��������� 2�� ��������
				{
					for (int j = 0; j<MatrixSize; j++)
					{
						if(Vmatrix[curInter[interNumber][i].v2][second_ort][temp[k].states[curInter[interNumber][i].n2]][j]!=0)
						{
							for(int oldst=0;oldst<N;oldst++)
								tempst.states[oldst]=temp[k].states[oldst];
							tempst.states[curInter[interNumber][i].n2]=j;

							curE=0;
							for(int eInd=0;eInd<N;eInd++)
								curE+=Energie[tempst.states[eInd]];

							if(curE!=E0)
							{
								tempst.factor=temp[k].factor*Vmatrix[curInter[interNumber][i].v2][second_ort][temp[k].states[curInter[interNumber][i].n2]][j];

								tempst.coeff[0]=temp[k].coeff[0];
								tempst.coeff[1]=temp[k].coeff[1];
								tempst.coeff[2]=temp[k].coeff[2];

								temp2.push_back(tempst);  //���������� � �������� ������
								add_state_to_map(temp2)
							}
						}
					}
				}
			}
		}
	}
	//��������� � �������� �������� ������
	outv.clear();
	if(temp2.size())
		collect(outv,temp2);

}

/* #2 */void act_ground(vector<state> &inv, vector<state> &outv, double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize], int interNumber)
{
	state tempst;
	int second_ort;
	//bool flag;
	temp2.clear();
	double curE,E0;
	E0=Energie[0]*N;

	//test
	/*static int sti=0;
	sti++;
	ofstream testout;
	if(sti==1)testout.open("testout.txt",ios::out);*/
	//end test

	for(int inSt=0;inSt<inv.size();inSt++)
	{
		for(int i=0;i<interAmount[interNumber];i++) //���������� ��� ��-�� ��������������
		{
			//temp2.clear();
			//�-�������
			for(int ort=0;ort<3;ort++)
			{
				temp.clear();//������� ��������� ������ ���������, ����� ��� y � z ���������
				for (int j = 0; j<MatrixSize; j++)//��������� ��������� ����������� 1�� �����-
				{
					if(Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j]!=0)
					{
						//��� 1�� ������� ��� �����, ������ ���� ��������

						if(ort==1||ort==0)//�-����� �������, �� ���� �������� �� -1, ������ 1 ���
							tempst.factor=inv[inSt].factor*0.5*Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j];
						else
							tempst.factor=inv[inSt].factor*Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j];
						//�������� ������ ���������, ��� ��� �� ����� ����� ����� ��������
						for(int oldst=0;oldst<N;oldst++)
							tempst.states[oldst]=inv[inSt].states[oldst];

						//������ ���������
						tempst.states[curInter[interNumber][i].n1]=j;

						tempst.coeff[0]=inv[inSt].coeff[0];
						tempst.coeff[1]=inv[inSt].coeff[1];
						tempst.coeff[2]=inv[inSt].coeff[2];
						//������ ��� �������� ������ ������ ��������!!!
						tempst.coeff[curInter[interNumber][i].Jtype]++;

						temp.push_back(tempst);
					}
				}
				//if(sti==1)testout<<"temp size="<<temp.size()<<"\n";
				switch(ort)
				{
				case 0: second_ort=1; break;
				case 1: second_ort=0; break;
				case 2: second_ort=2; break;
				}
				for(int k=0;k<temp.size();k++) //��������� �� ���������� ��������� 2�� ��������
				{
					for (int j = 0; j<MatrixSize; j++)
					{
						if(Vmatrix[curInter[interNumber][i].v2][second_ort][temp[k].states[curInter[interNumber][i].n2]][j]!=0)
						{
							for(int oldst=0;oldst<N;oldst++)
								tempst.states[oldst]=temp[k].states[oldst];
							tempst.states[curInter[interNumber][i].n2]=j;

							curE=0;
							for(int eInd=0;eInd<N;eInd++)
								curE+=Energie[tempst.states[eInd]];

							if(curE==E0)
							{
								tempst.factor=temp[k].factor*Vmatrix[curInter[interNumber][i].v2][second_ort][temp[k].states[curInter[interNumber][i].n2]][j];

								tempst.coeff[0]=temp[k].coeff[0];
								tempst.coeff[1]=temp[k].coeff[1];
								tempst.coeff[2]=temp[k].coeff[2];

								temp2.push_back(tempst);  //���������� � �������� ������
							}
						}
					}
				}
				//if(sti==1)testout<<"temp2 size="<<temp2.size()<<"\n";
			}
		}
	}
	//��������� � �������� �������� ������
	outv.clear();
	if(temp2.size())
		collect(outv,temp2);
	//testout.close();

}

/* #3 */void act_energy(vector<state> &inv, vector<state> &outv, double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize], int interNumber)
{
	state tempst;
	int second_ort;
	double curE,E0;

	temp2.clear();
	if(inv.size()>50)
		temp2.reserve(30000);
	outv.clear();
	E0=N*Energie[0];
	for(int inSt=0;inSt<inv.size();inSt++)
	{


		for(int i=0;i<interAmount[interNumber];i++) //���������� ��� ��-�� ��������������
		{
			//temp2.clear();
			//�-�������
			for(int ort=0;ort<3;ort++)
			{
				temp.clear();//������� ��������� ������ ���������, ����� ��� y � z ���������
				for (int j = 0; j<MatrixSize; j++)//��������� ��������� ����������� 1�� �����-
				{
					if(Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j]!=0)
					{
						//��� 1�� ������� ��� �����, ������ ���� ��������

						if(ort==1||ort==0)//�-����� �������, �� ���� �������� �� -1, ������ 1 ���
							tempst.factor=inv[inSt].factor* 0.5*Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j];
						else
							tempst.factor=inv[inSt].factor*Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j];
						//�������� ������ ���������, ��� ��� �� ����� ����� ����� ��������
						for(int oldst=0;oldst<N;oldst++)
							tempst.states[oldst]=inv[inSt].states[oldst];

						//������ ���������
						tempst.states[curInter[interNumber][i].n1]=j;

						tempst.coeff[0]=inv[inSt].coeff[0];
						tempst.coeff[1]=inv[inSt].coeff[1];;
						tempst.coeff[2]=inv[inSt].coeff[2];;
						//������ ��� �������� ������ ������ ��������!!!
						tempst.coeff[curInter[interNumber][i].Jtype]++;

						temp.push_back(tempst);
					}
				}
				switch(ort)
				{
				case 0: second_ort=1; break;
				case 1: second_ort=0; break;
				case 2: second_ort=2; break;
				}
				for(int k=0;k<temp.size();k++) //��������� �� ���������� ��������� 2�� ��������
				{
					for (int j = 0; j<MatrixSize; j++)
					{
						if(Vmatrix[curInter[interNumber][i].v2][second_ort][temp[k].states[curInter[interNumber][i].n2]][j]!=0)
						{
							for(int oldst=0;oldst<N;oldst++)
								tempst.states[oldst]=temp[k].states[oldst];
							tempst.states[curInter[interNumber][i].n2]=j;

							curE=0;
							for(int eInd=0;eInd<N;eInd++)
								curE+=Energie[tempst.states[eInd]];


							if(curE!=E0)
							{
								tempst.factor=temp[k].factor*Vmatrix[curInter[interNumber][i].v2][second_ort][temp[k].states[curInter[interNumber][i].n2]][j]/(E0-curE);
								tempst.coeff[0]=temp[k].coeff[0];
								tempst.coeff[1]=temp[k].coeff[1];
								tempst.coeff[2]=temp[k].coeff[2];

								temp2.push_back(tempst);  //���������� � �������� ������
							}

						}
					}
				}
			}
		}


		//��������� � �������� �������� ������
		//outv.clear();
		//printState(temp2,"bef.txt");

	}
	if(temp2.size())
		collect(outv,temp2);

}

/* #4 */void act_energy_power(vector<state> &inv, vector<state> &outv, int power, double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize], int interNumber)
{
	state tempst;
	int second_ort;
	//bool flag;
	double curE,E0;

	temp2.clear();
	if(inv.size()>50)
		temp2.reserve(30000);
	outv.clear();
	E0=N*Energie[0];
	for(int inSt=0;inSt<inv.size();inSt++)
	{


		for(int i=0;i<interAmount[interNumber];i++) //���������� ��� ��-�� ��������������
		{
			//temp2.clear();
			//�-�������
			for(int ort=0;ort<3;ort++)
			{
				temp.clear();//������� ��������� ������ ���������, ����� ��� y � z ���������
				for (int j = 0; j<MatrixSize; j++)//��������� ��������� ����������� 1�� �����-
				{
					if(Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j]!=0)
					{
						//��� 1�� ������� ��� �����, ������ ���� ��������

						if(ort==1||ort==0)//�-����� �������, �� ���� �������� �� -1, ������ 1 ���
							tempst.factor=inv[inSt].factor* 0.5*Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j];
						else
							tempst.factor=inv[inSt].factor*Vmatrix[curInter[interNumber][i].v1][ort][inv[inSt].states[curInter[interNumber][i].n1]][j];
						//�������� ������ ���������, ��� ��� �� ����� ����� ����� ��������
						for(int oldst=0;oldst<N;oldst++)
							tempst.states[oldst]=inv[inSt].states[oldst];
						/*tempst.states[0]=inv[inSt].states[0];
						tempst.states[1]=inv[inSt].states[1];
						tempst.states[2]=inv[inSt].states[2];*/

						//������ ���������
						tempst.states[curInter[interNumber][i].n1]=j;

						tempst.coeff[0]=inv[inSt].coeff[0];
						tempst.coeff[1]=inv[inSt].coeff[1];;
						tempst.coeff[2]=inv[inSt].coeff[2];;
						//������ ��� �������� ������ ������ ��������!!!
						tempst.coeff[curInter[interNumber][i].Jtype]++;

						temp.push_back(tempst);
					}
				}
				switch(ort)
				{
				case 0: second_ort=1; break;
				case 1: second_ort=0; break;
				case 2: second_ort=2; break;
				}
				for(int k=0;k<temp.size();k++) //��������� �� ���������� ��������� 2�� ��������
				{
					for (int j = 0; j<MatrixSize; j++)
					{
						if(Vmatrix[curInter[interNumber][i].v2][second_ort][temp[k].states[curInter[interNumber][i].n2]][j]!=0)
						{
							tempst.factor=temp[k].factor*Vmatrix[curInter[interNumber][i].v2][second_ort][temp[k].states[curInter[interNumber][i].n2]][j];

							/*
							tempst.states[0]=temp[k].states[0];
							tempst.states[1]=temp[k].states[1];
							tempst.states[2]=temp[k].states[2];*/
							for(int oldst=0;oldst<N;oldst++)
								tempst.states[oldst]=temp[k].states[oldst];
							tempst.states[curInter[interNumber][i].n2]=j;

							tempst.coeff[0]=temp[k].coeff[0];
							tempst.coeff[1]=temp[k].coeff[1];
							tempst.coeff[2]=temp[k].coeff[2];


							curE=0;
							for(int eInd=0;eInd<N;eInd++)
							{
								curE+=Energie[tempst.states[eInd]];
							}


							if(curE!=E0)
							{
								tempst.factor=tempst.factor/pow((E0-curE),power);
								temp2.push_back(tempst);  //���������� � �������� ������
							}

						}
					}
				}
			}
		}


		//��������� � �������� �������� ������
		//outv.clear();
		//printState(temp2,"bef.txt");

	}
	if(temp2.size())
	collect(outv,temp2);

}

/* #5 */void act_inside(vector<state> &inv,vector<state> &outv,int plaquetNumber)
{
	state tempst;
	double curE,E0;
	E0=N*Energie[0];
	temp.clear();
	for(int inSt=0;inSt<inv.size();inSt++)
	{
		for (int j = 0; j<MatrixSize; j++)
		{
			if(VmatrixInside[inv[inSt].states[plaquetNumber]][j]!=0)
			{


				for(int oldst=0;oldst<N;oldst++)
					tempst.states[oldst]=inv[inSt].states[oldst];
				tempst.states[plaquetNumber]=j;

				curE=0;
				for(int eInd=0;eInd<N;eInd++)
					curE+=Energie[tempst.states[eInd]];

				if(E0!=curE)
				{

					tempst.factor=inv[inSt].factor*VmatrixInside[inv[inSt].states[plaquetNumber]][j];

					tempst.coeff[0]=inv[inSt].coeff[0];
					tempst.coeff[1]=inv[inSt].coeff[1];
					tempst.coeff[2]=inv[inSt].coeff[2]+1;

					temp.push_back(tempst);
				}

			}
		}
	}
	outv.clear();
	if(temp.size())
		collect(outv,temp);

}

/* #6 */void act_inside_enrgy_power(vector<state> &inv,vector<state> &outv,int power,int plaquetNumber)
{
	state tempst;
	double curE,E0;
	E0=N*Energie[0];
	temp.clear();
	for(int inSt=0;inSt<inv.size();inSt++)
	{
		for (int j = 0; j<MatrixSize; j++)
		{
			if(VmatrixInside[inv[inSt].states[plaquetNumber]][j]!=0)
			{


				for(int oldst=0;oldst<N;oldst++)
					tempst.states[oldst]=inv[inSt].states[oldst];
				tempst.states[plaquetNumber]=j;

				curE=0;
				for(int eInd=0;eInd<N;eInd++)
					curE+=Energie[tempst.states[eInd]];

				if(E0!=curE)
				{

					tempst.factor=inv[inSt].factor*VmatrixInside[inv[inSt].states[plaquetNumber]][j]/pow(double(E0-curE),power);

					tempst.coeff[0]=inv[inSt].coeff[0];
					tempst.coeff[1]=inv[inSt].coeff[1];
					tempst.coeff[2]=inv[inSt].coeff[2]+1;

					temp.push_back(tempst);
				}

			}
		}
	}
	outv.clear();
	if(temp.size())
		collect(outv,temp);

}

/* #7 */void act_inside_ground(vector<state> &inv,vector<state> &outv,int plaquetNumber)
{
	state tempst;
	double curE,E0;
	E0=N*Energie[0];
	temp.clear();
	for(int inSt=0;inSt<inv.size();inSt++)
	{
		for (int j = 0; j<MatrixSize; j++)//���������� ��� �������� ������� ������ ������� ��������
		{
			if(VmatrixInside[inv[inSt].states[plaquetNumber]][j]!=0)
			{


				for(int oldst=0;oldst<N;oldst++)
					tempst.states[oldst]=inv[inSt].states[oldst];
				tempst.states[plaquetNumber]=j;

				curE=0;
				for(int eInd=0;eInd<N;eInd++)
					curE+=Energie[tempst.states[eInd]];

				if(E0==curE)
				{

					tempst.factor=inv[inSt].factor*VmatrixInside[inv[inSt].states[plaquetNumber]][j];

					tempst.coeff[0]=inv[inSt].coeff[0];
					tempst.coeff[1]=inv[inSt].coeff[1];
					tempst.coeff[2]=inv[inSt].coeff[2]+1;

					temp.push_back(tempst);
				}

			}
		}
	}
	outv.clear();
	if(temp.size())
		collect(outv,temp);

}



void generate_procedure_order(int *termorder,int* operatororder,int edge_amount,int num,int *Res,int *power)
{
	for(int i=0;i<num;i++)
	{
		power[i]=0;
	}
	for(int i=0;i<(num+1)/2;i++)
	{
		if(termorder[i]==0)//ground ������
		{
			if(operatororder[i]<edge_amount)//�������� ��������
				Res[i]=2;
			else
				Res[i]=7;
		}
		else if(termorder[i]==1)//����������� � 1�� �������
		{
			if(operatororder[i]<edge_amount)
				Res[i]=3;
			else
			{
				Res[i]=6;
				power[i]=1;
			}

		}
		else
		{
			if(operatororder[i]<edge_amount)
				Res[i]=4;
			else
				Res[i]=6;
			power[i]=termorder[i];
		}
	}

	//�������� ���
	for(int i=0;i<(num/2);i++)
	{
		if(termorder[num-i-2]==0)//ground ������
		{
			if(operatororder[num-i-1]<edge_amount)//�������� ��������
				Res[num-i-1]=2;
			else
				Res[num-i-1]=7;
		}
		else if(termorder[num-i-2]==1)//����������� � 1�� �������
		{
			if(operatororder[num-i-1]<edge_amount)
				Res[num-i-1]=3;
			else
			{
				Res[num-i-1]=6;
				power[num-i-1]=1;
			}

		}
		else
		{
			if(operatororder[num-i-1]<edge_amount)
				Res[num-i-1]=4;
			else
				Res[num-i-1]=6;
			power[num-i-1]=termorder[num-i-2];
		}
	}
	//����� ��������� ������� ��������� ���� ��� �����������
	if((Res[num-num/2]==3)||(Res[num-num/2]==4))
		Res[num-num/2]=1;
	if(Res[num-num/2]==6)
		Res[num-num/2]=5;

}
