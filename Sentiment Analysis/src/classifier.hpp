#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class NaiveBayes {
 public:
  void train(const std::vector<std::string>& texts,
             const std::vector<int>& labels);
  int predict(const std::string& text);

 private:
  std::unordered_map<std::string, std::vector<double>> word_probs;
  double prior_pos = 0.5;
};
