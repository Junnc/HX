#include "WSClient.h"
#include <unistd.h>
#include <thread>
#include <map>


int main(int argc, char* const argv[])
{
	auto ip = "futures-quote-test.hengxifintech.com";
	auto port = 80;

	//const char* ip = "139.224.233.67";
	//int port = 5522;

	//CWSClient wsClient("127.0.0.1", 5555);
	CWSClient wsClient(ip, port);
	wsClient.Run();
	//auto content = "<HX>{\"cmdcode\" :1000}<END>"; 

	//wsClient.SendWebSocket(content);
	pause();
}

/*
 *int main(){
 *        
 *        int j = 10;
 *        int l = 1000;
 *
 *        std::map<int, CWSClient*> cliMap;
 *        for(auto i = 0; i != j; i++) {
 *                cliMap[i] = new CWSClient("127.0.0.1", 5555);
 *        }
 *        
 *        for(auto i = 0; i != j; i++) {
 *        std::thread th([&]{
 *                //CWSClient wsClient("127.0.0.1", 5555);
 *                cliMap[i]->Start();
 *                //auto content = "<HX>{\"cmdcode\" :1000}<END>"; 
 *                auto content = "ping"; 
 *
 *                for (auto k = 0; k != l; k++) {
 *                        cliMap[i]->SendWebSocket(content);
 *                }
 *        });
 *        th.join();
 *        }
 *        pause();
 *}
 */
