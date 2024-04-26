#include <iostream>
#include <string>
#include "cmdline.h"

int main(int argc, char **argv){
    cmdline::parser cmdParser;
    cmdParser.add<std::string>("vocab", 'v', "specify mllm tokenizer model path", false, "../vocab/llama_vocab.mllm");
    cmdParser.add<std::string>("model", 'm', "specify mllm model path", false, "../models/llama-2-7b-chat-q4_k.mllm");
    cmdParser.add<int>("limits", 'l', "max KV cache size", false, 400);
    cmdParser.add<int>("thread", 't', "num of threads", false, 4);
    cmdParser.parse_check(argc, argv);

    std::string vocab_path = cmdParser.get<std::string>("vocab");
    std::string model_path = cmdParser.get<std::string>("model");

    std::cout << "vocab" << std::endl;
    return 0;
}

