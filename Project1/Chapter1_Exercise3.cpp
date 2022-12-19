// 사무실 공유 프린터의 인쇄 대기 목록 시뮬레이션
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
			os << "id: " << j.id << ", 사용자: " << j.user << ",  페이지수: " << j.pages << "장";
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
				cout << "인쇄 대기열에 추가 실패: " << job << endl;
				return false;
			}

			cout << "인쇄 대기열에 추가 : " <<job<< endl;
			jobs.push(job);
			return true;
		}

		void startPrinting() {
			while (not jobs.empty()) {
				cout << "인쇄 중: " << jobs.front() << endl;
				jobs.pop();
			}
		}
};

int main()
{
	Printer<5> printer;

	Job j1("광희", 10);
	Job j2("정다", 4);
	Job j3("현수", 5);
	Job j4("유미", 7);
	Job j5("채원", 8);
	Job j6("시원", 10);

	printer.addNewJob(j1);
	printer.addNewJob(j2);
	printer.addNewJob(j3);
	printer.addNewJob(j4);
	printer.addNewJob(j5);
	printer.addNewJob(j6); // 인쇄 대기열이 가득 차있어서 추가할 수 없음
	printer.startPrinting();

	printer.addNewJob(j6); // 인쇄 대기열이 비었으므로 추가 가능
	printer.startPrinting();
}