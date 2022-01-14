#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
	unordered_map<int, string> ui;

	
	//Buckets
	for (int i = 0; i < 10; i++) {
		ui.insert(make_pair(i, "123"));
		cout << i << ": max_bucket_count=" << ui.max_bucket_count() << ", bucket_count=" << ui.bucket_count() << endl;
		cout << i << ": load_factor=" << ui.load_factor() << ", max_load_factor=" << ui.max_load_factor() << endl;
	}

	ui.rehash(100);

	cout << "5. max_bucket_count=" << ui.max_bucket_count() << ", bucket_count=" << ui.bucket_count() << endl;
	cout << "5. load_factor=" << ui.load_factor() << ", max_load_factor=" << ui.max_load_factor() << endl;

	ui.reserve(6);

	cout << "6. max_bucket_count=" << ui.max_bucket_count() << ", bucket_count=" << ui.bucket_count() << endl;
	cout << "6. load_factor=" << ui.load_factor() << ", max_load_factor=" << ui.max_load_factor() << endl;

	ui.reserve(1000);

	cout << "7. max_bucket_count=" << ui.max_bucket_count() << ", bucket_count=" << ui.bucket_count() << endl;
	cout << "7. load_factor=" << ui.load_factor() << ", max_load_factor=" << ui.max_load_factor() << endl;

	return 0;
}
