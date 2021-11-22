#include <iostream>
#include <map>
#include <set>

using namespace std;
/**
* IP packages
* id -> offset
* id -> key    //+src
*   1. 使用key区分IP，再使用key做组合：(虽然用了，但只有模糊印象，照猫画虎，画过就忘。)
*      map->ip.id，第一次要构造一个set。 
*            (+src一起判断顺序，且不使用udphdr)。//第二次看。
*      set->ip.fragement，insert到set中(去重&排序)。
*   1. multi-map : check offset：不同主键能保持有序（lhs），相同主键按插入顺序排序：
*        本身是rbt
*   2. assembly :
*        0包,UPD len.
*   
* ？lhs：left handle struct
* ？pair: 不接受构造型参数，c++17以下不能推导<>，要使用make_pair,可以自动推导<>
* ？map[]，自动调用缺省构造
* ？struct内的bool()=>整体作为重载符号，是判断真假用的（引用，对象，指针？ => 都ok，但是判断的是对象，指针要加*使用）
* ？使用using替代typedef
* ？比较function的类函数是const形式的【construct定义中是const的】
* ？单独调用仿函数，声明一个对象，拿对象名做函数名调用【使用default构造，作compare方法的时候】
* ？如果把cout，写在函数外，但是在namespace中，可能会报cout不能识别
* 
*/
namespace duMultiMap {
    class solution {
    public:
        static void test() {
            multimap<int, int, bool(*)(int, int)> a([](int l, int r) ->bool { if (l < r) return true; else return false; });
            a.insert(make_pair(5, 1));
            a.insert(make_pair(1, 9));
            a.insert(make_pair(1, 1));
            a.insert(make_pair(5, 2));
            a.insert(make_pair(1, 2));
            a.insert(make_pair(1, 1));

            //直接遍历1:9,1,2
            for (auto [key, val] : a) {
                cout << "[key, val] = " << key << "," << val << endl;
            }
            cout << "<=================map multi====================" << endl;

            //查找值1:9,1,2
            for (auto it = a.find(1); it->first == 1; it++) {
                cout << "[key, val] = " << it->first << "," << it->second << endl;
            }
            cout << "<=================one multi====================" << endl;

            multiset<pair<int, int>> b;
            for (auto i = a.begin(); i != a.end(); i++)
                b.insert(*i);

            //less使用了pair的<，pair的<是先比较key，再比较value
            for (auto [key, val] : b) {
                cout << "[key, val] = " << key << "," << val << endl;
            }
            cout << "<=================set multi====================" << endl;
        }
    };
}

namespace duMapSet {
    class solution {
    public:
        static void test() {
            map<int, set<pair<int, int>>> ms;

            //ms.insert( pair(5, set<pair<int, int>>()) );
            ms[5].insert(make_pair(5, 1));
            ms[1].insert(make_pair(1, 9));
            ms[1].insert(make_pair(1, 1));
            ms[5].insert(make_pair(5, 2));
            ms[1].insert(make_pair(1, 2));
            ms[1].insert(make_pair(1, 1));

            for (auto [k, v] : ms) {
                for (auto vset : v) {
                    cout << "[key, val] = " << k << "," << vset.second << endl;
                }
            }
        }
    };
}


namespace duIpAssembly {
#define MTU 1500
#define IP_HD_LEN 20
    struct iphdr {
        int id;
        int src;
        bool fragment;
        int offset;
        int len;
    };

    //struct udphdr {
    //    int len;
    //};

    struct fragmentPackageKey {
        fragmentPackageKey() = default;
        int id;
        int src;
        int seq;
        //udphdr uhdr;
        operator bool() { return id; }
        fragmentPackageKey(int seq, const iphdr& ihdr) :seq(seq), id(ihdr.id), src(ihdr.src) {}//, const udphdr& uhdr) :seq(seq), id(ihdr.id) {}//, uhdr(uhdr) {}
        bool operator() (const fragmentPackageKey& lhs, const fragmentPackageKey& rhs) const { if(lhs.id != rhs.id) return lhs.id < rhs.id; else return lhs.src < rhs.src;
        }
        bool operator< (const fragmentPackageKey& rhs) { return id < rhs.id; }
    };

    struct fragmentPackageVal {
        fragmentPackageVal() = default;
        iphdr ihdr;
        char buf[MTU+1];
        operator bool() { return ihdr.fragment; }
        fragmentPackageVal(const iphdr& ihdr, const char* buf) :ihdr(ihdr){ memset(this->buf, 0, MTU+1); memcpy(this->buf, buf, ihdr.len); }
        bool operator() (const fragmentPackageVal& lhs, const fragmentPackageVal& rhs) const { return lhs.ihdr.offset < rhs.ihdr.offset; }
        bool operator< (const fragmentPackageVal& rhs) { return ihdr.offset < rhs.ihdr.offset; }
    };

    struct compareKey {
        bool operator() (const fragmentPackageKey& lhs, const fragmentPackageKey& rhs) const { return lhs.id < rhs.id; }
    };

    struct compareVal {
        bool operator() (const fragmentPackageVal& lhs, const fragmentPackageVal& rhs) const { return lhs.ihdr.offset < rhs.ihdr.offset; }
    };

    typedef set<fragmentPackageVal, fragmentPackageVal> ipFragmentSet;
    typedef map<fragmentPackageKey, ipFragmentSet, fragmentPackageKey > ipFragmentMap;

    class solution {
    public:
        static void test() {
            //测试比较函数
            ipFragmentMap ipPacks;

            fragmentPackageKey ipKey = fragmentPackageKey(1, { 1, 123456, true, 0, 1500 });// , { 1500 - 8 - 20 + 1500 - 20 + 1 });
            fragmentPackageVal ipVal1 = fragmentPackageVal({ 1, 123456, true, 0, 1500 }, "abcdefghijklmnopqrst0123456789111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111119876543210");
            fragmentPackageVal ipVal2 = fragmentPackageVal({ 1, 123456, false, 2960, 21 }, "abcdefghijklmnopqrst3");
            //和外部是匹配的，此处干掉了匹配过程
            //fragmentPackageVal ipVal3 = fragmentPackageVal({ 2, false, 1501, 21 }, "b");
            fragmentPackageVal ipVal4 = fragmentPackageVal({ 1, 123456, true, 1480, 1500 }, "abcdefghijklmnopqrst0123456789222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222229876543210");
            
            //test for ()
            //fragmentPackageVal _fragmentPackageVal;
            //cout << "status = " << _fragmentPackageVal(ipVal1, ipVal2) << endl;

            ipPacks[ipKey].insert(ipVal1);
            ipPacks[ipKey].insert(ipVal2);
            //ipPacks[ipKey].insert(ipVal3);//和外部是匹配的，此处干掉了匹配过程
            ipPacks[ipKey].insert(ipVal4);

            //test for save order
            for (auto& [k, v] : ipPacks) {
                for (auto& vset : v) {
                    cout << k.id << ":" << vset.ihdr.id << ":" << vset.ihdr.offset << endl;
                }
            }

            //assemably
            for (auto& [k, v] : ipPacks) {
                bool flag = false;
                int correctLen = 0;
                char payload[65535] = "";
                int paylen = 0;
                for (auto& vset : v) {
                    cout << k.id << ":" << vset.ihdr.id << ":" << vset.ihdr.offset << endl;
                    //1.中间不空包
                    if (correctLen != vset.ihdr.offset) {
                        cout << k.id << ":" << "mid not completed." << endl;
                        break;
                    }
                    if (!vset.ihdr.offset) {
                        memcpy(payload + paylen, vset.buf, vset.ihdr.len);
                        paylen += vset.ihdr.len;
                    }
                    else {
                        memcpy(payload + paylen, vset.buf + IP_HD_LEN, vset.ihdr.len - IP_HD_LEN);
                        paylen += (vset.ihdr.len - IP_HD_LEN);
                    }
                    correctLen += (vset.ihdr.len - IP_HD_LEN);
                    
                    //2.最后不是尾巴
                    flag = vset.ihdr.fragment;
                }

                if (flag) {
                    cout << k.id << ":" << "tail not completed." << endl;
                    break;
                }

                cout << "payload[" << paylen << "] = " << payload << endl;
            }

            auto st_true = fragmentPackageVal({ 2, 123456, true, 1501, 21 }, "b");
            auto st_false = fragmentPackageVal({ 2, 123456, false, 1501, 21 }, "b");
            cout << "bool() = " << st_true << " : " << st_false << endl;
            auto* pr_true = new fragmentPackageVal({ 2, 123456, true, 1501, 21 }, "b");
            auto* pr_false = new fragmentPackageVal({ 2, 123456, false, 1501, 21 }, "b");
            cout << "bool() = " << pr_true << " : " << pr_false << endl;
            cout << "bool() = " << *pr_true << " : " << *pr_false << endl;

            auto &f1 = st_true;
            auto &f2 = st_false;
            auto &f3 = *pr_true;
            auto &f4 = *pr_false;

            cout << "bool() = " << f1 << " : " << f2 << " : " << f3 << " : " << f4 << endl;
        }
    };
}


int main()
{
    //duMultiMap::solution::test();
    
    //duMapSet::solution::test();

    duIpAssembly::solution::test();

    return 0;
}