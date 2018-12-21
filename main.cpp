#include <iostream>
#include <iomanip>
#include <fstream>//����/����ļ�����
#include <cstring>
#include <string>
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
    map<int, int> saleProsMap; //����ũ��Ʒ
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

    void salePro(int proNo, int num)//��ũ��Ʒ
    {

        saleProsMap.insert(pair<int, int>(proNo, num));
    }

    void disp()//����ۻ�Ա��Ϣ
    {
        cout << setw(10) << "����Ա���" << setw(15) << "����\t" << setw(20) << "������[��Ʒ���x����]\n";
        cout << setw(10) << no << setw(15) << name.c_str() <<setw(20)<< "[";
        map<int, int>::iterator iter;
        for (iter = saleProsMap.begin(); iter != saleProsMap.end(); iter++)

            cout << iter->first << "x" << iter->second <<" ; ";
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
        if (p == NULL) {
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
    char choice = 'a',rtemp[20];
    string rname, phone;
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
                cin >> rtemp;
                rname = rtemp;
                cout << "��������Ա�Ա�(0��1Ů):";
                cin >> sex;
                addSalesman(salesmanID, rname, sex, phone);
                break;
            case '2':
                cout << "��������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == NULL) {
                    cout << " ������Ա������ " << endl;
                    break;
                }
                cout << "�����µ�����:";
                char rtemp[20];
                cin >> rtemp;
                rname = rtemp;
                r->setname(rname);
                break;
            case '3':
                cout << " ��������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == NULL) {
                    cout << " ������Ա������" << endl;
                    break;
                }
                r->delman();
                break;
            case '4':
                cout << "��������Ա��ţ�С��ʮλ��:";
                cin >> salesmanID;
                r = query(salesmanID);
                if (r == NULL) {
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
            case '0':
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
    string name;//����
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

    int getPriceTol() { return priceTol; }

    void delPro() { tag = 1; }//ɾ��ũ��Ʒ
    void addPro(int n, string na, int p, int nu)//����ũ��Ʒ
    {
        tag = 0;
        no = n;
        name = na;
        price = p;
        num = nu;
        priceTol = p * nu;
    }
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

    int addPro(int n, string na, int pri, int nu)//���ũ��Ʒ
    {
        Production *p = query(n);
        if (NULL == p) {
            top++;
            production[top].addPro(n, na, pri, nu);
            return 1;
        } else {
            p->addpriceTol(pri * nu);
        }
        return 0;
    }

    Production *query(int proID)//����ũ��Ʒ
    {
        for (int i = 0; i <= top; i++)
            if (production[i].getno() == proID ) {
                return &production[i];
            }
        return NULL;
    }

    void proSort() {
        for (int i = 0; i < top ; ++i) {
            for (int j = 0; j < top  - i; ++j) {
                if (production[i].getPriceTol() < production[j].getPriceTol()) {
                    Production temp = production[i];
                    production[i] = production[j];
                    production[j] = temp;
                }
            }
        }
    }

    void disp() {
        cout << setw(20) << "ũ��Ʒ���" << setw(20) << "����" << setw(20)
             << "�����۶�" << endl;
        for (int i = 0; i <= top; ++i) {
            cout << setw(20) << production[i].getno() << setw(20) << production[i].getname() << setw(20)
                 << production[i].getPriceTol() << endl;
        }
    }

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
    int saleID, proID, mouth, num, price, priceTol;
public:
    int getPriceTol() const {
        return priceTol;
    }

private:
    string salename, proname;//����
public:
    const string &getSalename() const {
        return salename;
    }

    const string &getProname() const {
        return proname;
    }

    int getSaleID() { return saleID; }

    int getProID() { return proID; }

    int getMouth() { return mouth; }

    int getNum() { return num; }

    int getPrice() { return price; }

    void addMouthMes(int sid, int pid, int mou, int pri, int nu, string sname, string pname) {
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
        cout << setw(10) << saleID << setw(15) << salename.c_str() << setw(10) << proID << setw(15) << proname.c_str()<<setw(10)
             << mouth << setw(15) << price << setw(15) << num << setw(15) << priceTol << endl;
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

    int addMouthData(int sid, int pid, int mou, int pri, int nu, string sname, string pname)//���
    {
        Mouth *p = query(sid, pid, mou);
        if (NULL == p) {
            top++;
            mouth[top].addMouthMes(sid, pid, mou, pri, nu, sname, pname);
            return 1;
        }
        return 0;
    }

    Mouth *query(int sid, int pid, int mou)//����
    {

        for (int i = 0; i <= top; i++) {

            if (mouth[i].getSaleID() == sid && mouth[i].getProID() == pid && mouth[i].getMouth() == mou) {

                return &mouth[i];
            }
        }
        return NULL;
    }

    Mouth *query(int mou)//����
    {

        for (int i = 0; i <= top; i++) {

            if (mouth[i].getMouth() == mou) {

                mouth[i].disp();
            }
        }
        return NULL;
    }

    void mouSort() {
        for (int i = 0; i < top ; ++i) {
            for (int j = 0; j < top  - i; ++j) {
                if (mouth[i].getSaleID() < mouth[j].getSaleID()) {
                    Mouth temp = mouth[i];
                    mouth[i] = mouth[j];
                    mouth[j] = temp;
                }
            }
        }
    }

    void count() {
        mouSort();
        int i = 0;
        while (i <= top) {
            int sID = mouth[i].getSaleID();
            int pID = mouth[i].getProID();
            int tol = mouth[i].getPriceTol();
            int count = 1;
            cout <<setw(10)<< sID<<setw(15)<<mouth[i].getSalename() <<setw(10)<<pID;
            while (mouth[++i].getSaleID() == sID && mouth[i].getProID() == pID) {

                count++;
                tol += mouth[i].getPriceTol();
                if (i == top) {
                    break;
                }
            }
            cout<<setw(15) << tol / count << endl;

        }
    }

};


//main() ������ʵ�֣�����������������
int main() {
    char choice = 'a';
    int proID, salesmanID, sex, num, price, priceTol, date;

    string phone, pname;

    char sname[20], guige[20];
    SDatabase salesmanData;
    Salesman *s;
    PDatabase proData;
    Production *p;
    MouthDataBase mouthDataBase;
    Mouth *m;
    while (choice != 'q') {
        cout <<"=================================================================="<< endl << "\t\t ũ��Ʒ���� �� �� ϵ ͳ\n\n\n";
        cout
                << "\t\t\t1 ¼��������Ϣ\n\n\t\t\t2 ����Աά�� \n\n\t\t\t3 ����Ա����ͳ��\n\n\t\t\t4 ũ��Ʒ����ͳ��\n\n\t\t\t5 �¶ȱ���\n\n\t\t\t6 ������Ա�����۶�\n\n==================================================================\n"
                << endl;
        
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
                char phtemp[20];
                cin >> phtemp;
                phone = phtemp;
                while (phone.length() > 11) {
                    cout << "�绰��Ч������������" << endl;

                    cin >> phtemp;
                    phone = phtemp;

                }
                cout << " ��Ʒ��ţ�С��ʮλ���� ";
                cin >> proID;
                cout << " ��Ʒ���ƣ� ";
                char ntemp[20];
                cin >> ntemp;
                pname = ntemp;
                while (pname == " ") {
                    cout << "������Ч��������" << endl;

                    cin >> ntemp;
                    pname = ntemp;

                }
                cout << " ��Ʒ���С��20λ���� ";
                cin >> guige;
                cout << " ��Ʒ������ ";
                cin >> num;
                cout << " ��Ʒ���ۣ� ";
                cin >> price;

                cout << " ��������(��ʽ20190101)�� ";
                cin >> date;
                while (date / 100 % 100 <= 0 || date / 100 % 100 >= 12) {
                    cout << "������Ч����������" << endl;
                    cin >> date;
                }
                salesmanData.addSalesman(salesmanID, sname, sex, phone);
                proData.addPro(proID, pname, price, num);
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
                proData.proSort();
                proData.disp();
                break;
            case '5':
                int moutemp;
                cout << "�������·�(��ʽ��201901)" << endl;
                cin >> moutemp;
                cout << setw(10) << "ҵ��Ա���" << setw(15) << "����" << setw(10) << "��Ʒ���" << setw(15) << "��Ʒ����" << setw(10)
                     << "�·�" << setw(15) << "����" << setw(15) << "����" << setw(15) << "�ܼ�" << endl;
                mouthDataBase.query(moutemp);
                break;
            case '6':
                cout <<setw(10)<< "����Ա����" <<setw(15)<< "����\t" <<setw(10)<< "��Ʒ���\t" <<setw(15)<< "ƽ�������۶�" << endl;
                mouthDataBase.count();
                break;
            default:
                cout << "���������������룺";
        }
    }
    return 0;
}