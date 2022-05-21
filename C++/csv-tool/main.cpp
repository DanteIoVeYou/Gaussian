#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
#define COL_NUM 12

int main()
{
  vector<vector<string> > ret;
  ifstream in("./data");
  if(in.is_open()) {
    string line;
    while(getline(in, line)) {
      vector<string> everyline;
      string str;
      for(size_t i = 0; i < line.size(); i++) {
        if(line[i] != ',') {
          str += line[i];
        }
        else {
          if(line[i-1] == ',') {
            str = "X";
            everyline.push_back(str);
            str.clear();
          }
          else {
            everyline.push_back(str);
            str.clear();
          }
        }
      } 
      str.resize(str.size()-1);
#ifdef DEBUG
      cout << "===" << str << "@@@" << endl;
#endif
      everyline.push_back(str);
      ret.push_back(everyline);
    }

    // 计算每列的平均值
    double arr[COL_NUM];
    for(size_t k = 1; k < COL_NUM; k++) {
      double sum = 0;
      for(size_t m = 1; m < ret.size(); m++) {
        if(ret[m][k] != "X" || ret[m][k] != "X\r")
          sum += atof(ret[m][k].c_str());
      }
      arr[k] = sum / (ret.size()-1);
      cout << k << " " << arr[k] << endl;
    }

    // 寻找X的位置
    for(size_t i = 0; i < ret.size(); i++) {
      if(find(ret[i].begin(), ret[i].end(), "X") != ret[i].end() || find(ret[i].begin(), ret[i].end(), "X\r") != ret[i].end()) {
        cout << "行号：" << i + 1 << " " << "位置： ";
        for(size_t j = 0; j < COL_NUM; j++) {
          if(ret[i][j] == "X"  || ret[i][j] == "") {
            cout << j + 1 << " ";
            ret[i][j] = to_string(arr[j]);
          }
        }
        cout << endl;
      }
    }
  }
  else {
    cerr << "open file failed" << endl;
    return 1;
  }

  // 写入输出文件
  ofstream out("output.csv");
  if(out.is_open()) {
    for(size_t i = 0; i < ret.size(); i++) {
      ret[i].back() += "\r\n";
      for(size_t j = 0; j < ret[i].size(); j++) {
        if(j != ret[i].size() - 1) {
          out << ret[i][j];
          out << ",";
        }
        else {
          out << ret[i][j];
        }
      }
    }
  }
  else {
    cerr << "create file failed" << endl;
    return 2;
  }
#ifdef DEBUG
  for(size_t i = 0; i < ret.size(); i++) {
    for(size_t j = 0; j < ret[i].size(); j++) {
      cout << ret[i][j] << " ";
    }
  } 
#endif
  return 0;
}
