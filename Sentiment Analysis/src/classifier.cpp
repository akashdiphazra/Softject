#include "classifier.hpp"

#include <cmath>
#include <sstream>

void NaiveBayes::train(const std::vector<std::string>& texts,
                       const std::vector<int>& labels) {
  std::unordered_map<std::string, std::vector<int>> word_counts;
  int count_pos = 0, count_neg = 0;

  for (size_t i = 0; i < texts.size(); ++i) {
    std::istringstream iss(texts[i]);
    std::string word;
    while (iss >> word) {
      word_counts[word].resize(2);
      word_counts[word][labels[i]] += 1;
    }
    if (labels[i] == 1)
      count_pos++;
    else
      count_neg++;
  }

  prior_pos = static_cast<double>(count_pos) / (count_pos + count_neg);
  for (auto& [word, counts] : word_counts) {
    double total_pos = counts[1] + 1;
    double total_neg = counts[0] + 1;
    double total = count_pos + count_neg + 2;
    word_probs[word] = {std::log(total_neg / total),
                        std::log(total_pos / total)};
  }
}

int NaiveBayes::predict(const std::string& text) {
  std::istringstream iss(text);
  std::string word;
  double log_prob_neg = std::log(1 - prior_pos);
  double log_prob_pos = std::log(prior_pos);

  while (iss >> word) {
    if (word_probs.count(word)) {
      log_prob_neg += word_probs[word][0];
      log_prob_pos += word_probs[word][1];
    }
  }

  return log_prob_pos > log_prob_neg ? 1 : 0;
}
