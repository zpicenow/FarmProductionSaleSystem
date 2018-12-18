#include <iostream>
#include <iomanip>
#include <fstream>//����/����ļ�����
#include <cstring>

using namespace std;
const int Maxr = 100;//����Ա�������
const int Maxb = 100;//ũ��Ʒ�������
const int Maxper = 100;//ÿ������Ա��������
//����Ա��
class Salesman {
private:
    int tag; //ɾ����� 1:��ɾ 0:δɾ
    int no; //����Ա����
    char name[10]; //����Ա����
    int sex;//0��1Ů
    char phone[11];//��ϵ�绰
    int salePros[Maxper];//����ũ��Ʒ
public:
    Salesman() {}

    char *getname() { return name; } //��ȡ����
    int gettag() { return tag; } //��ȡɾ�����
    int getno() { return no; } //��ȡ����Ա����
    void setname(char na[]) //��������
    {
        strcpy(name, na);
    }

    void delman() { tag = 1; }//����ɾ����� 1:��ɾ 0:δɾ
    void addSaleMan(int n, char *na)//��������Ա
    {
        tag = 0;
        no = n;
        strcpy(name, na);
        for (int i = 0; i < Maxper; i++)
            salePros[i] = 0;
    }

    void salePro(int proNo)//��ũ��Ʒ
    {
        for (int i = 0; i < Maxper; i++) {
            if (salePros[i] == 0) {
                salePros[i] = proNo;
                return;
            }
        }
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
        cout << setw(5) << no << setw(10) << name << "������Ʒ��ţ�С��ʮλ����[";
        for (int i = 0; i < Maxper; i++)
            if (salePros[i] != 0)
                cout << salePros[i] << "|";
        cout << "]" << endl;
    }
};

//����Ա�⣬��������Ա��ȫ����Ϣ
class SDatabase {
private:
    int top; //����Ա��¼ָ��
    Salesman sale[Maxr];//����Ա��¼
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

    int addSalesman(int n, char *na)//�������Աʱ�Ȳ����Ƿ����
    {
        Salesman *p = query(n);
        if (p == nullptr) {
            top++;
            sale[top].addSaleMan(n, na);
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
};

void SDatabase::salesmanData() {
    char choice;
    char rname[20];
    int salesmanID;
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
                addSalesman(salesmanID, rname);
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
    char name[20];//����
    int price;//��Ʒ����
public:
    Production() {}

    char *getname() { return name; }//����
    int getno() { return no; }//��ȡũ��Ʒ���
    int gettag() { return tag; }//��ȡɾ�����
    void setname(char na[])//��������
    {
        strcpy(name, na);
    }

    void delPro() { tag = 1; }//ɾ��ũ��Ʒ
    void addPro(int n, char *na, int p)//����ũ��Ʒ
    {
        tag = 0;
        no = n;
        strcpy(name, na);
        price = p;
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
    int top; //��¼ָ��
    Production production[Maxb]; //ũ��Ʒ��¼
public:
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

    int addPro(int n, char *na, int pri)//���ũ��Ʒ
    {
        Production *p = query(n);
        if (nullptr == p) {
            top++;
            production[top].addPro(n, na, pri);
            return 1;
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
    int proID, salesmanID, sex,num,price;


    char sname[20], phone[11], pname[20], guige[20];
    SDatabase salesmanData;
    Salesman *s;
    PDatabase proData;
    Production *p;
    while (choice != '0') {
        cout << endl << endl << "\t\t\t ũ��Ʒ���� �� �� ϵ ͳ\n\n\n";
        cout << "\t\t\t1 ¼��������Ϣ\n\n\t\t\t2 �� �� \n\n\t\t\t3 ͼ �� ά ��\n\n\t\t\t4 �� �� ά ��\n\n\t\t\t0 �� ��" << endl;
        cin >> choice;
        switch (choice) {
            case '1':
                cout << " ����������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                cout << " ����������Ա����:";
                cin >> sname;
                cout << " ����������Ա�Ա�(0��1Ů):";
                cin >> sex;
                cout << " ����������Ա��ϵ�绰:";
                cin >> phone;
                cout << " ��Ʒ��ţ�С��ʮλ���� ";
                cin >> proID;
                cout << " ��Ʒ���ƣ� ";
                cin >> pname;
                cout << " ��Ʒ���С��20λ���� ";
                cin >> guige;
                cout << " ��Ʒ������ ";
                cin >> num;
                cout << " ��Ʒ���ۣ� ";
                cin >> price;

                break;
            case '2':
                cout << "����\n ���߱�ţ�С��ʮλ��:";
                cin >> salesmanID;
                cout << " ͼ���ţ�С��ʮλ��:";
                cin >> proID;
                s = salesmanData.query(salesmanID);
                if (s == NULL) {
                    cout << " �����ڸö��ߣ����ܻ���" << endl;
                    break;
                }
                p = proData.query(proID);
                if (p == NULL) {
                    cout << " �����ڸ�ͼ�飬���ܻ���" << endl;
                    break;
                }
//                p->retbook();
//                s->retbook(p->getno());
                break;
            case '3':
                proData.prodata();
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