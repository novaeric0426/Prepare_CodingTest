// �繫�� ���� �������� �μ� ��� ��� �ùķ��̼�
#include<iostream>
#include<queue>

using namespace std;

class Job {
	int id;
	string user;
	int pages;

	static int count;

	public:
		Job(const string& u, int p) :user(u), pages(p), id(++count) {}

		friend ostream& operator<<(ostream& os, const Job& j) {
			os << "id: " << j.id << ", �����: " << j.user << ",  ��������: " << j.pages << "��";
			return os;
		}
};

int Job::count = 0;

template<size_t N>
class Printer {
	queue<Job> jobs;

	public:
		bool addNewJob(const Job& job) {
			if (jobs.size() == N) {
				cout << "�μ� ��⿭�� �߰� ����: " << job << endl;
				return false;
			}

			cout << "�μ� ��⿭�� �߰� : " <<job<< endl;
			jobs.push(job);
			return true;
		}

		void startPrinting() {
			while (not jobs.empty()) {
				cout << "�μ� ��: " << jobs.front() << endl;
				jobs.pop();
			}
		}
};

int main()
{
	Printer<5> printer;

	Job j1("����", 10);
	Job j2("����", 4);
	Job j3("����", 5);
	Job j4("����", 7);
	Job j5("ä��", 8);
	Job j6("�ÿ�", 10);

	printer.addNewJob(j1);
	printer.addNewJob(j2);
	printer.addNewJob(j3);
	printer.addNewJob(j4);
	printer.addNewJob(j5);
	printer.addNewJob(j6); // �μ� ��⿭�� ���� ���־ �߰��� �� ����
	printer.startPrinting();

	printer.addNewJob(j6); // �μ� ��⿭�� ������Ƿ� �߰� ����
	printer.startPrinting();
}