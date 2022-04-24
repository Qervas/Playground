/*
 * @Author: FrankTudor
 * @Date: 2022-04-24 10:43:09
 * @LastEditors: FrankTudor
 * @Description: This file is created, edited, contributed by FrankTudor
 * @LastEditTime: 2022-04-24 12:00:14
 */
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
class Solution {
public:
using p =  pair<int,int> ;
    vector<int> intersection(vector<vector<int>>& nums) {
        vector<int> answer;
        map<int,int> m;
        int key = 0;
        for(int i = 0; i < nums.size(); i++){
            for(int j = 0; j < nums[i].size(); j++){
                key = nums[i][j];
                if(0 == m.count(key)){
                    m.insert({key,1});
                }else{
                    m[key]++;
                }
            }
        }
        vector<p> _list(m.size());
        auto j=_list.begin();
        for(auto i = m.begin();i != m.end(); i++,j++){
            (*j)= {(*i).second, (*i).first};
        }
        sort(_list.begin(),_list.end(),[](const p& a, const p& b){return a.first > b.first;});
		for(auto k = _list.begin(); k != _list.end();k++){
			if((*k).first == nums.size()){
                answer.push_back((*k).second);
            }else{
                break;
            }
		}
        sort(answer.begin(), answer.end(), [](const int & a, const int & b){return a<b;});
        return answer;
        
    }
};
int main(void){
    vector<vector<int>> vec{{3,1,2,4,5},{1,2,3,4},{3,4,5,6}};
    Solution s;
    vector<int> answer = s.intersection(vec);
    for(int& x:answer){
        cout << x << ", ";
    }
    return 0;
}
