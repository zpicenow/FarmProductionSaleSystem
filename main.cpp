#include <iostream>
#include <iomanip>
#include <fstream>//����/����ļ�����
#include <cstring>
#include <map>

using namespace std;
const int Maxr = 100;//����Ա�������
const int Maxb = 100;//ũ��Ʒ�������
const int Maxper = 100;//ÿ������Ա��������
const int MaxMouth = 100;//���100��������

//����Ա��
class Salesman {
private:
    int tag; //ɾ����� 1:��ɾ 0:δɾ
    int no; //����Ա����
    string name; //����Ա����
    int sex;//0��1Ů
    string phone;//��ϵ�绰
    map<int,int> saleProsMap; //����ũ��Ʒ
//    int salePros[Maxper];
public:
    Salesman() {}

    string getname() { return name; } //��ȡ����
    int gettag() { return tag; } //��ȡɾ�����
    int getno() { return no; } //��ȡ����Ա����
    void setname(string na) //��������
    {
        name = na;
    }

    void delman() { tag = 1; }//����ɾ����� 1:��ɾ 0:δɾ
    void addSaleMan(int n, string na, int se, string ph)//��������Ա
    {
        tag = 0;
        no = n;
        sex = se;
        name = na;
        phone = ph;


    }

    void salePro(int proNo,int num)//��ũ��Ʒ
    {

        saleProsMap.insert(pair<int, int>(proNo, num));
    }

    /*int retbook(int bookid)//�������
    {
        for(int i=0;i<Maxper;i++)
        {
            if(salePros[i]==bookid)
            {
                salePros[i]=0;
                return 1;
            }
        }
        return 0;
    }*/
    void disp()//����ۻ�Ա��Ϣ
    {
        cout << setw(5) << no << setw(10) << name << "������Ʒ��[";
        map<int, int>::iterator iter;
        for(iter = saleProsMap.begin(); iter != saleProsMap.end(); iter++)

            cout<<iter->first<<' X '<<iter->second<<endl;
        cout << "]" << endl;
    }
};

//����Ա�⣬��������Ա��ȫ����Ϣ
class SDatabase {
//����Ա��¼ָ��
    //����Ա��¼
public:
    SDatabase() //���캯������reader.txt����read[]��
    {
        Salesman s;
        top = -1;
        fstream file("salesman.txt", ios::in);//��һ�������ļ�
        while (1) {
            file.read((char *) &s, sizeof(s));
            if (!file)break;
            top++;
            sale[top] = s;
        }
        file.close(); //�ر� �ļ�
    }

    void clear()//ɾ����������Ա��Ϣ
    {
        top = -1;
    }

    int addSalesman(int n, string na, int se, string ph)//�������Աʱ�Ȳ����Ƿ����
    {

        Salesman *p = query(n);
        if (p == nullptr) {
            top++;
            sale[top].addSaleMan(n, na, se, ph);
            return 1;
        }
        return 0;
    }

    Salesman *query(int salesmanID)//����Ų�������Ա
    {
        for (int i = 0; i <= top; i++)
            if (sale[i].getno() == salesmanID &&
                sale[i].gettag() == 0) {
                return &sale[i];
            }
        return NULL;
    }

    void disp() //�����������Ա��Ϣ
    {
        for (int i = 0; i <= top; i++)
            sale[i].disp();
    }

    void salesmanData();//����Ա��ά��
    ~SDatabase() //������������slae[]д��salesman.txt�ļ���
    {
        fstream file("salesman.txt", ios::out);
        for (int i = 0; i <= top; i++)
            if (sale[i].gettag() == 0)
                file.write((char *) &sale[i], sizeof(sale[i]));
        file.close();
    }

    Salesman sale[Maxr];
    int top;
};

void SDatabase::salesmanData() {
    char choice;
    string rname,phone;
    int salesmanID;
    int sex;
    Salesman *r;
    while (choice != '0') {
        cout
                << "\n\n\t\t\t����Ա ά ��\n\n\n\t\t 1 �� ��\n\n\t\t 2 �� ��\n\n\t\t 3 ɾ ��\n\n\t\t 4 �� ��\n\n\t\t 5 �� ʾ\n\n\t\t 6 ���\n\n\t\t 0 �� ��"
                << endl;
        cin >> choice;
        switch (choice) {
            case '1':
                cout << "��������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                cout << "��������Ա����:";
                cin >> rname;
                cout << "��������Ա�Ա�(0��1Ů):";
                cin >> sex;
                addSalesman(salesmanID, rname, sex,phone);
                break;
            case '2':
                cout << "��������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == nullptr) {
                    cout << " ������Ա������ " << endl;
                    break;
                }
                cout << "�����µ�����:";
                cin >> rname;
                r->setname(rname);
                break;
            case '3':
                cout << " ��������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == nullptr) {
                    cout << " ������Ա������" << endl;
                    break;
                }
                r->delman();
                break;
            case '4':
                cout << "��������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == nullptr) {
                    cout << "������Ա������" << endl;
                    break;
                }
                r->disp();
                break;
            case '5':
                disp();
                break;
            case '6':
                clear();
                break;
            default:
                cout << "���������������룺";
                break;
        }
    }
}

//ũ��Ʒ�࣬ʵ�ֶ�ũ��Ʒ������
class Production {
private:
    int tag;//ɾ����� 1:��ɾ 0:δɾ
    int no;//ũ��Ʒ���
    string  name;//����
    int num;
    int price;//��Ʒ����
    int priceTol;
public:
    Production() {}

    string getname() { return name; }//����
    int getno() { return no; }//��ȡũ��Ʒ���
    int gettag() { return tag; }//��ȡɾ�����

    void addpriceTol(int tol)//��������
    {
        priceTol += tol;
    }

    void delPro() { tag = 1; }//ɾ��ũ��Ʒ
    void addPro(int n, string na, int p,int nu)//����ũ��Ʒ
    {
        tag = 0;
        no = n;
        name = na;
        price = p;
        num = nu;
        priceTol = p * nu;
    }
    /*int borrowbook()//�������
    {
        if (onshelf==1)
        {
            onshelf=0;
            return 1;
        }
        return 0;
    }*/
    /*void retbook()//�������
    {
        onshelf=1;
    }*/
    /*void disp()//���ͼ��
    {
        cout << setw(6) << no << setw(18) << name << setw(10)
             <<(onshelf==1? "�ڼ�":"�ѽ�") <<endl;
    }*/
};

//ũ��Ʒ�⣬ʵ�ֶ�ũ��Ʒ�Ĺ���
class PDatabase {
private:
public:
    int top; //��¼ָ��
    Production production[Maxb]; //ũ��Ʒ��¼
    PDatabase()//���캯������txt����Production[]��
    {
        Production b;
        top = -1;
        fstream file("Production.txt", ios::in);
        while (1) {
            file.read((char *) &b, sizeof(b));
            if (!file) break;
            top++;
            production[top] = b;
        }
        file.close();
    }

    void clear()//ȫɾ
    {
        top = -1;
    }

    int addPro(int n, string na, int pri,int nu)//���ũ��Ʒ
    {
        Production *p = query(n);
        if (nullptr == p) {
            top++;
            production[top].addPro(n, na, pri,nu);
            return 1;
        } else {
            p->addpriceTol(pri * nu);
        }
        return 0;
    }

    Production *query(int proID)//����ũ��Ʒ
    {
        for (int i = 0; i <= top; i++)
            if (production[i].getno() == proID && production[i].gettag() == 0) {
                return &production[i];
            }
        return nullptr;
    }

    void prodata();//ũ��Ʒά��
    /*void disp()
    {
        for (int i=0;i<=top;i++)
            if (production[i].gettag()==0)
                production[i].disp();
    }*/
    ~PDatabase()//������������
    {
        fstream file("production.txt", ios::out);
        for (int i = 0; i <= top; i++)
            if (production[i].gettag() == 0)
                file.write((char *) &production[i], sizeof(production[i]));
        file.close();
    }
};
//������
class Mouth {
private:
    int saleID,proID,mouth,num,price,priceTol;
    string salename,proname;//����
public:

    int getSaleID() { return saleID; }
    int getProID() { return proID; }
    int getMouth() { return mouth; }
    int getNum() { return num; }
    int getPrice() { return price; }

    void addMouthMes(int sid,int pid,int mou,int pri,int nu,string sname,string pname)
    {
        saleID = sid;
        proID = pid;
        mouth = mou;
        price = pri;
        num = nu;
        salename = sname;
        proname = pname;
        priceTol = pri * nu;
    }
    void disp()//���
    {
        cout << setw(10) << saleID << setw(10) << salename << setw(10) << proID << setw(10) << proname
             << mouth << setw(10) << price << setw(10) << num << setw(10) << priceTol << endl;
    }
};

//�������⣬
class MouthDataBase {
private:
public:
    int top = -1; //��¼ָ��
    Mouth mouth[MaxMouth]; //��¼


    void clear()//ȫɾ
    {
        top = -1;
    }

    int addMouthData(int sid,int pid,int mou,int pri,int nu,string sname,string pname)//���
    {
        Mouth *p = query(sid,pid,mou);
        if (nullptr == p) {
            top++;
            mouth[top].addMouthMes(sid,pid,mou,pri,nu,sname,pname);
            return 1;
        }
        return 0;
    }

    Mouth *query(int sid,int pid,int mou)//����
    {
        for (int i = 0; i <= top; i++)
            if (mouth[i].getSaleID() == sid && mouth[i].getProID() == pid && mouth[i].getMouth() == mou) {
                return &mouth[i];
            }
        return nullptr;
    }

};

void PDatabase::prodata() {
    char choice;
    char bname[40];
    int pri;
    int proID;
    Production *b;
    while (choice != '0') {
        cout << "\n\n\n\t\t\tũ��Ʒ ά �� " << endl << endl;
        cout << "\t\t1 �� ��\n \t\t2 �� ��\n\t\t3 ɾ ��\n\t\t4 �� ��\n\t\t5 �� ʾ\n\t\t6 ȫ ɾ\n\t\t0 �� ��" << endl;
        cin >> choice;
        switch (choice) {
            case '1':
                cout << "�����Ʒ��ţ�С��ʮλ��:" << endl;
                cin >> proID;
                cout << "����ũ��Ʒ��:" << endl;
                cin >> bname;
                cout << "����ũ��Ʒ����:" << endl;
                cin >> pri;
                addPro(proID, bname, pri);
                break;
            case '2':
                cout << "�����Ʒ��ţ�С��ʮλ��:" << endl;
                cin >> proID;
                b = query(proID);
                if (b == nullptr) {
                    cout << " �ò�Ʒ������ " << endl;
                    break;
                }
                cout << "�����µ�����:" << endl;
                cin >> bname;
                b->setname(bname);
                break;
            case '3':
                cout << " �����Ʒ��ţ�С��ʮλ��:" << endl;
                cin >> proID;
                b = query(proID);
                if (b == nullptr) {
                    cout << " �ò�Ʒ������" << endl;
                    break;
                }
                b->delPro();
                break;
//            case '4':
//                cout << " �����Ʒ���:"<<endl;
//                cin >> proID;
//                b=query(proID);
//                if (b== nullptr)
//                {
//                    cout <<" ��ͼ�鲻����"<< endl;
//                    break;
//                }
//                b->disp();
//                break;
//            case '5':
//                disp();
//                break;
            case '6':
                clear();
                break;
            default:
                cout << "����������������:";
        }
    }
}

//main() ������ʵ�֣�����������������
int main() {
    char choice;
    int proID, salesmanID, sex, num, price, priceTol,date;

    string phone, pname;

    char sname[20], guige[20];
    SDatabase salesmanData;
    Salesman *s;
    PDatabase proData;
    Production *p;
    MouthDataBase mouthDataBase;
    Mouth *m;
    while (choice != '0') {
        cout << endl << endl << "\t\t\t ũ��Ʒ���� �� �� ϵ ͳ\n\n\n";
        cout << "\t\t\t1 ¼��������Ϣ\n\n\t\t\t2 ����Աά�� \n\n\t\t\t3 ������Ϣ����\n\n\t\t\t4 �� �� ά ��\n\n\t\t\t0 �� ��" << endl;
        cin >> choice;
        switch (choice) {
            case '1':
                cout << " ����������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                cout << " ����������Ա����:";
                cin >> sname;
                cout << " ����������Ա�Ա�(0��1Ů):";
                cin >> sex;
                while (sex != 0 && sex != 1) {
                    cout << "�Ա���Ч����������" << endl;
                    cin >> sex;
                }
                cout << " ����������Ա��ϵ�绰:";
                cin >> phone;
                while (phone.length() > 11) {
                    cout << "�绰��Ч������������" << endl;

                    cin >> phone;

                }
                cout << " ��Ʒ��ţ�С��ʮλ���� ";
                cin >> proID;
                cout << " ��Ʒ���ƣ� ";
                cin >> pname;
                while (pname == " ") {
                    cout << "������Ч��������" << endl;

                    cin >> pname;

                }
                cout << " ��Ʒ���С��20λ���� ";
                cin >> guige;
                cout << " ��Ʒ������ ";
                cin >> num;
                cout << " ��Ʒ���ۣ� ";
                cin >> price;

                cout << " ��������(��ʽ20190101)�� ";
                cin >> date;
                salesmanData.addSalesman(salesmanID, sname, sex, phone);
                proData.addPro(proID, pname, price);
                salesmanData.sale[salesmanData.top].salePro(proID, num);
                mouthDataBase.addMouthData(salesmanID, proID, date / 100, price, num, sname, pname);
                break;
            case '2':
                salesmanData.salesmanData();
                break;
            case '3':
                int sID;
                cout << "����������Ա����" << endl;
                cin >> sID;
                salesmanData.query(sID)->disp();
                break;
            case '4':
                salesmanData.salesmanData();
                break;
            default:
                cout << "���������������룺";
        }
    }
    return 0;
}