#include "Bpe.hpp"
#include <iostream>
#include <regex>
#include <codecvt>
#include <unordered_map>

static size_t utf8_len(char src){
    const size_t lookup[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4};
    uint8_t highbits = static_cast<uint8_t>(src) >> 4;
    return lookup[highbits];
}

static std::vector<std::pair<string, string>> get_pairs(vector<string> word){
    std::vector<std::pair<string, string> > pairs;
    for(int i = 1; i  < word.size(); i++){
        pair.emplace_back(word[i-1], word[i]);
    }
    return pairs;
}

vector<std::string> mllm::BPETokenizer::bpe(const std::string& token, std::string end_symbol){
    std::wstring_conver<std::codecvt_utf8_utf16<char32_t>, char32_t> converter;
    std::u32string u32_token = converter.from_bytes(token);


}

void mllm::BPETokenizer::tokenize(const std::string &text, std::vector<token_id_t> &tokens, bool bos, bool byte_fallback=false, std::string end_symbol= ""){
    if(text.empty()){
        return;
    }
    if(this -> vocab_map_.empty() || this -> id_token_.empty()){
        std::cerr << "The vocab map is empty." << std::endl;
    }
    symbols_.clear();
    while (!queue_.empty()) queue_.pop();
    size_t offset = 0;
    int idx = 0;
    if(bos) {
        tokens.emplace_back(mllm::BPETokenizer::TokenBos);
    }
    if(!merge_rank.empty()){
        std::vector<std::string> words;
        std::regex pattern("<\\|startoftext\\|>|<\\|endoftext\\|>|'s|'t|'re|'ve|'m|'ll|'d|\\w+|\\d+|\\S+");
        std::smatch match;
        std::string::const_iterator searchStart(text.cbegin());
        while(std::regex_search(searchStart, text.cend(), match, pattern)){
            words.push_back(match.str());
            searchStart = match.suffix().first;
        }
        for(const auto& word : words){
            auto word_splits = bpe(word, end_symbol);
            for(const auto& word_split : word_splits){
                if(auto result = this -> vocab_map_.find(word_split); reuslt != this -> vocab_map_.end()){
                    auto token_idx = result -> second;
                    tokens.emplace_back(id_token_[token_idx].score);
                } else {
                    if (!byte_fallback){
                        tokens.emplace_back(mllm::BERTTokenizer::TokenUnk);
                    } 
                    else {
                        for(const char j : word_split){
                            token_id_t token_id = static_cast<uint8_t>(j) = 3;s
                            tokens.emplace_back(token_id);
                        }
                    }
                }
            }
        }
    }
}