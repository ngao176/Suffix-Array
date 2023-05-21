#include <string>
#include <vector>
#include <algorithm> 
#include "SuffixArray.h"
using namespace std;

/**
 * Implement suffix_array() correctly
 */
vector<unsigned int> suffix_array(const string & s) {
    /* YOUR CODE HERE */
    int n = s.size();
    vector<unsigned int> sa(n);
    vector<unsigned int> rnk(n);

    for (int i = 0; i < n; ++i){
      sa[i] = i;
      rnk[i] = s[i];
    } 

    for (int k = 1; k < n; k *= 2) {
      auto cmp = [&](int i, int j) {

        if (rnk[i] != rnk[j]){ 
            return rnk[i] < rnk[j];
        }

        int ri;
        if (i + k < n) {
            ri = rnk[i + k];
        } else {
            ri = -1;
        }

        int rj;
        if (j + k < n) {
            rj = rnk[j + k];
        } else {
            rj = -1;
        }
        
        return ri < rj;
      };
      sort(sa.begin(), sa.end(), cmp);
      vector<unsigned int> tmp(n);
      tmp[sa[0]] = 0;
      for (int i = 1; i < n; ++i){
        tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
      }
      swap(rnk, tmp);
    }
  return sa;
}
