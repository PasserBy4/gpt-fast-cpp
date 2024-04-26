#include <iostream>
#include "cmdline.h"

int main(int argc, char **argv){
    cmdline::parser cmdParser;
    cmdParser.add<string>("vocab", 'v', "specify converted tokenizer model path" , false, "../vocab/llama_vocab.mllm")
    cmdParser.add<string>("model", 'm', "specify converted model path", false, "../models/llama-2-7b-chat-q4_k.mllm")
    cmdParser.add<int>("limits", 'l', "max KV cache size", false, 400)
    cmdParser.add<int>("thread", 't', "num of threads", false, 4)
    cmpParser.parse_check(argc, argv);

    string vocab_path = cmdParser.get<string>("vocab");
    string model_path = cmdParser.get<string>("model");
    int token_limit = cmdParser.get<int>("limits");

    cout << "vocab: " << vocab_path << endl;
    return 0;
}

