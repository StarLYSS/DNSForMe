﻿#include<stdio.h>
#include<stdlib.h>
int Boot();
int UserInterface();
int RunLocalDNSServer();
int NetFixTool();
int WeakDNSMode();
int ConfigEditor();
int ConfigToDefault();
int NSTool();
int Help();
int FixHosts();
int Config_gen();
int Reset();
int ChangeVPNRoute();
int ResetVPNRoute();
int Checkdll();


int mode,DNSSet,fixmode,DNSServer,ADSwitch,Geo_Mode,RouteSwitch;
FILE* yaml,*AdGuardHome,*SystemHosts,*bak,*ADFilter,*AddRouteRules,*DelRouteRules,*AddDNSRoutes,*DelDNSRoutes,*dll;
char ADFilterRules[536],domain[50],NSCommand[72],Adapter[60],Command[120],Geo_List[2162];
char TopDNS[287] = "  - 208.67.222.222:5353\n  - 208.67.220.220:5353\n  - 208.67.222.220:5353\n  - 208.67.220.222:5353\n  - 208.67.222.222:443\n  - 208.67.220.220:443\n  - 208.67.222.220:443\n  - 208.67.220.222:443\n  - 2620:119:35::35:443\n  - 2620:119:35::35:5353\n  - 2620:119:53::53:443\n  - 2620:119:53::53:5353\n";
char Rewrite[100]="  - domain: '*.workers.dev'\n    answer: 1.0.0.1\n  - domain: '*.cloudflare.com'\n    answer: 1.0.0.1\n";
char WhiteList[2159]="  - '[/netease.com/]119.29.29.29'\n  - '[/126.net/]119.29.29.29'\n  - '[/icourse163.org/]119.29.29.29'\n  - '[/yeah.net/]119.29.29.29'\n  - '[/126.com/]119.29.29.29'\n  - '[/163.com/]119.29.29.29'\n  - '[/google.cn/]119.29.29.29'\n  - '[/baidu.com/]119.29.29.29'\n  - '[/baidupcs.com/]119.29.29.29'\n  - '[/bdstatic.com/]119.29.29.29'\n  - '[/bilibili.com/]119.29.29.29'\n  - '[/bilivideo.com/]119.29.29.29'\n  - '[/akamaized.net/]119.29.29.29'\n  - '[/hdslb.com/]119.29.29.29'\n  - '[/qq.com/]119.29.29.29'\n  - '[/douyu.com/]119.29.29.29'\n  - '[/huya.com/]119.29.29.29'\n  - '[/aliyun.com/]119.29.29.29'\n  - '[/alicdn.com/]119.29.29.29'\n  - '[/alipay.com/]119.29.29.29'\n  - '[/taobao.com/]119.29.29.29'\n  - '[/tmall.com/]119.29.29.29'\n  - '[/jd.com/]119.29.29.29'\n  - '[/zxxk.com/]119.29.29.29'\n  - '[/cnzz.com/]119.29.29.29'\n  - '[/chaoxing.com/]119.29.29.29'\n  - '[/snnu.edu.cn/]119.29.29.29'\n  - '[/ipip.net/]119.29.29.29'\n  - '[/7moor.com/]119.29.29.29'\n  - '[/t.cn/]119.29.29.29'\n  - '[/chinaz.com/]119.29.29.29'\n  - '[/uzer.me/]119.29.29.29'\n  - '[/lanzou.com/]119.29.29.29'\n  - '[/lanzous.com/]119.29.29.29'\n  - '[/baidupan.com/]119.29.29.29'\n  - '[/v.smtcdns.com/]119.29.29.29'\n  - '[/youku.com/]119.29.29.29'\n  - '[/ott.cibntv.net/]119.29.29.29'\n  - '[/zhihu.com/]119.29.29.29'\n  - '[/zhimg.com/]119.29.29.29'\n  - '[/cnki.net/]119.29.29.29'\n  - '[/iqiyi.com/]119.29.29.29'\n  - '[/qy.net/]119.29.29.29'\n  - '[/iqiyipic.com/]119.29.29.29'\n  - '[/acfun.cn/]119.29.29.29'\n  - '[/aixifan.com/]119.29.29.29'\n  - '[/yximgs.com/]119.29.29.29'\n  - '[/ksurl.cn/]119.29.29.29'\n  - '[/139.com/]119.29.29.29'\n  - '[/10086.cn/]119.29.29.29'\n  - '[/189.cn/]119.29.29.29'\n  - '[/knet.cn/]119.29.29.29'\n  - '[/10010.cn/]119.29.29.29'\n  - '[/10010.com/]119.29.29.29'\n  - '[/weibo.com/]119.29.29.29'\n  - '[/sina.com.cn/]119.29.29.29'\n  - '[/sohu.com/]119.29.29.29'\n  - '[/cctv.cn/]119.29.29.29'\n  - '[/nn.com/]119.29.29.29'\n  - '[/xunyou.com/]119.29.29.29'\n  - '[/leigod.com/]119.29.29.29'\n  - '[/gitee.io/]119.29.29.29'\n  - '[/eccdnx.com/]119.29.29.29'\n  - '[/iplaysoft.com/]119.29.29.29'\n  - '[/jianshu.com/]119.29.29.29'\n  - '[/edu.cn/]119.29.29.29'\n  - '[/gov.cn/]119.29.29.29'\n";
char Hosts[780]="- 151.101.248.133 raw.githubusercontent.com\n- 151.101.108.133 avatars2.githubusercontent.com\n- 151.101.76.133 avatars3.githubusercontent.com\n- 18.179.245.253 api.github.com\n- 23.160.0.107 video-weaver.arn03.hls.ttvnw.net\n- 45.113.131.6 video-weaver.hkg01.hls.ttvnw.net\n- 192.108.239.107 video-weaver.ams02.hls.ttvnw.net\n- 192.108.239.108 video-weaver.lhr03.hls.ttvnw.net\n- 52.223.241.1 video-weaver.sea01.hls.ttvnw.net\n- 52.223.241.2 video-weaver.atl01.hls.ttvnw.net\n- 52.223.241.3 video-weaver.hou01.hls.ttvnw.net\n- 52.223.241.5 video-weaver.iad03.hls.ttvnw.net\n- 52.223.241.7 video-weaver.lax03.hls.ttvnw.net\n- 23.41.76.251 store.steampowered.com\n- 1.0.0.1 www.v2ray.com\n- 1.0.0.1 v2ray.com\n- 1.0.0.1 www.pixiv.net.com\n- 1.0.0.1 justmysocks.net\n- 1.0.0.1 justmysocks2.net\n- \"\"\n";
char ABP_Filter[529]="\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/abp-filters-anti-cv.txt\n  name: ABP filters\n  id: 1588581704\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/easyprivacy.txt\n  name: EasyPrivacy\n  id: 1588581706\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/fanboy-social.txt\n  name: Fanboy's Social Blocking List\n  id: 1588581707\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/easylistchina+easylist.txt\n  name: EasyList China+EasyList\n  id: 1588581708\n";
char AdGuard_Filter[533]="\n- enabled: true\n  url: https://filters.adtidy.org/extension/chromium/filters/2.txt\n  name: AdGuard Base filter\n  id: 1589448814\n- enabled: true\n  url: https://filters.adtidy.org/extension/chromium/filters/3.txt\n  name: AdGuard Tracking Protection filter\n  id: 1589448815\n- enabled: true\n  url: https://filters.adtidy.org/extension/chromium/filters/4.txt\n  name: AdGuard Social Media filter\n  id: 1589448816\n- enabled: true\n  url: https://easylist-downloads.adblockplus.org/easylistchina.txt\n  name: EasyList China\n  id: 1589448817\n";


int main() {
MainMenu:system("cls");
	UserInterface();
	if (mode == 1) {
		Boot();
		if (Boot() != 0) {
			printf("未在软件目录中发现AdGuardHome引擎，请在官网下载后放置在本软件同一目录下！\n\n");
			system("pause");
			goto MainMenu;
		}
		Checkdll();
		if (Checkdll() != 0) {
			printf("无法找到cmroute.dll，请在网上下载后放入本程序目录下！\n");
			system("pause");
			goto MainMenu;
		}
		if (ChangeVPNRoute() == 0) {
			printf("\n执行国内外分流成功！\n");
		}
		else {
			printf("\n执行国内外分流失败！\n");
		}
		ChangeDNSRoute();
		RunLocalDNSServer();
		if (ResetVPNRoute() == 0) {
			printf("\n取消国内外分流成功！\n");
			}
		else {
			printf("\n取消国内外分流失败！\n");
			}
		goto MainMenu;
	}
	else if (mode == 2) {
		Boot();
		if (Boot() != 0) {
			printf("未在软件目录中发现AdGuardHome引擎，请在官网下载后放置在本软件同一目录下！\n\n");
			system("pause");
			goto MainMenu;
		}
		Checkdll();
		if (Checkdll() != 0) {
			printf("无法找到cmroute.dll，请在网上下载后放入本程序目录下！\n");
			system("pause");
			goto MainMenu;
		}
		ChangeDNSRoute();
		RunLocalDNSServer();
		goto MainMenu;
	}
	else if (mode == 3) {
		Checkdll();
		if (Checkdll() != 0) {
			printf("无法找到cmroute.dll，请在网上下载后放入本程序目录下！\n");
			system("pause");
			goto MainMenu;
		}
		printf("请选择运行模式：\n\n1.启动国内外分流\n\n2.关闭国内外分流\n\n请输入：");
		scanf("%d", &RouteSwitch);
		if (RouteSwitch == 1) {
			if (ChangeVPNRoute() == 0) {
				printf("\n执行成功！\n");
			}
			else {
				printf("\n执行失败！\n");
			}
		}
		else {
			if (ResetVPNRoute() == 0) {
				printf("\n执行成功！\n");
			}
			else {
				printf("\n执行失败！\n");
			}
		}
		goto MainMenu;
	}
	else if (mode == 4) {
		Checkdll();
		if (Checkdll() != 0) {
			printf("无法找到cmroute.dll，请在网上下载后放入本程序目录下！\n");
			system("pause");
			goto MainMenu;
		}
		NetFixTool();
		goto MainMenu;
	}
	else if (mode == 5) {
		Boot();
		if (Boot() != 0) {
			printf("未在软件目录中发现AdGuardHome引擎，请在官网下载后放置在本软件同一目录下！\n\n");
			system("pause");
			goto MainMenu;
		}
		ConfigEditor();
		goto MainMenu;
}
	else if (mode == 6) {
		Boot();
		if (Boot() != 0) {
			printf("未在软件目录中发现AdGuardHome引擎，请在官网下载后放置在本软件同一目录下！\n\n");
			system("pause");
			goto MainMenu;
		}
		ConfigToDefault();
		goto MainMenu;
}
	else if (mode == 7) {
		NSTool();
		goto MainMenu;
	}
	else if (mode == 8) {
		FixHosts();
		goto MainMenu;
	}
	else if (mode == 9) {
		Help();
		goto MainMenu;
}
	else if (mode == 0) {
		exit(0);
	}
	else {
		goto MainMenu;
	}
	return 0;
}

int Config_gen() {
	printf("注意：节点1、2为国内节点，解析速度更快，但可能会留下解析日志，使用请注意！\n\n");
	printf("指定上游DNS服务器区域：\n\n1.红鱼DNS（阿里云+腾讯云）（加密解析，但服务器在国内，安全性低，解析速度快，适合游戏）\n\n2.Cisco OpenDNS（中国香港）（未加密解析，服务器在国外，解析速度快，适合游戏）\n\n3.Cisco OpenDNS（中国香港）（加密解析，服务器在国外，安全性高）\n\n4.GoogleDNS（美国中部）（加密解析，服务器在国外，安全性高）\n\n5.AdGuardDNS（俄罗斯）（加密解析，服务器在国外，安全性高）\n\n6.IBM Quad9（美国中部）（加密解析，服务器在国外，安全性高）\n\n7.CloudflareDNS（中国香港）（加密解析，服务器在国外，无日志记录，安全性极高）\n\n8.SWITCH.CH DNS（瑞士苏黎世、洛桑）（加密解析，服务器在中立国，安全性极高）\n\n请输入：");
	scanf("%d", &DNSServer);
	system("cls");
	printf("广告拦截模式：\n\n1.开启Adblock Plus拦截\n\n2.开启AdGuard拦截\n\n3.不拦截\n\n请输入：");
	scanf("%d", &ADSwitch);
	system("cls");
	printf("启用国内外分流：\n\n1.启用分流\n\n2.全局模式\n\n请输入：");
	scanf("%d", &Geo_Mode);
		yaml = fopen("index.yaml", "w");
		if (ADSwitch == 1) {
			sprintf(ADFilterRules, "%s",ABP_Filter);

		}
		 else if (ADSwitch == 2) {
			sprintf(ADFilterRules, "%s", AdGuard_Filter);
		}
		else {
			sprintf(ADFilterRules, "[]\n");
		}
		if (Geo_Mode == 2) {
			sprintf(Geo_List, "");
		}
		else {
			sprintf(Geo_List, "%s",WhiteList);
		}
		if (DNSServer == 1)fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: true\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: true\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: \n%s  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", TopDNS,"  - tls://dns.rubyfish.cn\n", Geo_List, Rewrite, ADFilterRules,Hosts);
		else if (DNSServer == 2)fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: true\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: true\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: \n%s  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", TopDNS,  "  - 208.67.222.222:5353\n  - 208.67.220.220:5353\n  - 208.67.222.220:5353\n  - 208.67.220.222:5353\n  - 208.67.222.222:443\n  - 208.67.220.220:443\n  - 208.67.222.220:443\n  - 208.67.220.222:443\n  - https://doh.opendns.com/dns-query\n", Geo_List, Rewrite, ADFilterRules, Hosts);
		else if (DNSServer == 3)fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: true\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: true\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: \n%s  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", TopDNS,  "  - https://doh.opendns.com/dns-query\n", Geo_List, Rewrite, ADFilterRules, Hosts);
		else if (DNSServer == 4)fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: true\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: true\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: \n%s  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", TopDNS,  "  - tls://dns.google\n  - https://dns.google/dns-query\n", Geo_List, Rewrite, ADFilterRules, Hosts);
		else if (DNSServer == 5)fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: true\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: true\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: \n%s  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", TopDNS,  "  - tls://dns.adguard.com\n  - https://dns.adguard.com/dns-query\n", Geo_List, Rewrite, ADFilterRules, Hosts);
		else if (DNSServer == 6)fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: true\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: true\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: \n%s  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", TopDNS,  "  - https://dns.quad9.net/dns-query\n  - tls://dns.quad9.net\n", Geo_List, ADFilterRules, Hosts);
		else if (DNSServer == 7)fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: true\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: true\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: \n%s  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", TopDNS,  "  - tls://1dot1dot1dot1.cloudflare-dns.com\n  - https://dns.cloudflare.com/dns-query\n", Geo_List, Rewrite, ADFilterRules, Hosts);
		else fprintf(yaml, "bind_host: 0.0.0.0\nbind_port: 80\nusers:\n- name: root\n  password: $2a$10$mdmUKhmmhuDQO8GHlU.8xOWzwG6Fy.5o5YUCUWYg2DkyfgYRsM0hy\nhttp_proxy: ""\nlanguage: ""\nrlimit_nofile: 0\nweb_session_ttl: 720\ndns:\n  bind_host: 0.0.0.0\n  port: 53\n  statistics_interval: 1\n  querylog_enabled: true\n  querylog_interval: 90\n  querylog_size_memory: 1000\n  anonymize_client_ip: false\n  protection_enabled: true\n  blocking_mode: default\n  blocking_ipv4: \"\"\n  blocking_ipv6: \"\"\n  blocked_response_ttl: 10\n  ratelimit: 0\n  ratelimit_whitelist: []\n  refuse_any: true\n  bootstrap_dns:\n%s  all_servers: true\n  fastest_addr: false\n  edns_client_subnet: true\n  enable_dnssec: true\n  aaaa_disabled: false\n  allowed_clients: []\n  disallowed_clients: []\n  blocked_hosts: []\n  parental_block_host: family-block.dns.adguard.com\n  safebrowsing_block_host: standard-block.dns.adguard.com\n  cache_size: 0\n  cache_ttl_min: 0\n  cache_ttl_max: 0\n  upstream_dns:\n%s%s  filtering_enabled: true\n  filters_update_interval: 24\n  parental_enabled: false\n  safesearch_enabled: false\n  safebrowsing_enabled: false\n  safebrowsing_cache_size: 1048576\n  safesearch_cache_size: 1048576\n  parental_cache_size: 1048576\n  cache_time: 30\n  rewrites: \n%s  blocked_services: []\ntls:\n  enabled: false\n  server_name: \"\"\n  force_https: false\n  port_https: 443\n  port_dns_over_tls: 853\n  allow_unencrypted_doh: false\n  strict_sni_check: false\n  certificate_chain: \"\"\n  private_key: \"\"\n  certificate_path: \"\"\n  private_key_path: \"\"\nfilters: %swhitelist_filters: []\nuser_rules:\n%sdhcp:\n  enabled: false\n  interface_name: \"\"\n  gateway_ip: \"\"\n  subnet_mask: \"\"\n  range_start: \"\"\n  range_end: \"\"\n  lease_duration: 86400\n  icmp_timeout_msec: 1000\nclients: []\nlog_file: \"\"\nverbose: false\nschema_version: 6\n", TopDNS,  "  - https://dns.switch.ch/dns-query\n  - tls://dns.switch.ch\n", Geo_List, Rewrite, ADFilterRules, Hosts);
		fclose(yaml);
		system("cls");
		if(DNSServer==1)printf("\n已选定：%s\n\n","红鱼DNS（阿里云+腾讯云）");
		else if (DNSServer == 2)printf("\n已选定：%s\n\n", "Cisco OpenDNS（中国香港）未加密版");
		else if (DNSServer == 3)printf("\n已选定：%s\n\n", "Cisco OpenDNS（中国香港）加密版");
		else if (DNSServer == 4)printf("\n已选定：%s\n\n", "GoogleDNS（美国中部）");
		else if (DNSServer == 5)printf("\n已选定：%s\n\n", "AdGuardDNS（俄罗斯）");
		else if (DNSServer == 6)printf("\n已选定：%s\n\n", "IBM Quad9（美国中部）");
		else if (DNSServer == 7)printf("\n已选定：%s\n\n", "CloudflareDNS（中国香港）");
		else printf("\n已选定：%s\n\n", "SWITCH.CH DNS（瑞士苏黎世、洛桑）");
		if (ADSwitch == 1)printf("%s\n\n","已开启Adblock Plus广告拦截功能");
		else if (ADSwitch == 2)printf("%s\n\n", "已开启AdGuard广告拦截功能");
		else printf("%s\n\n", "已关闭广告拦截功能");
		if (Geo_Mode == 2)printf("%s\n\n", "已启用全局模式");
		else printf("%s\n\n", "已开启DNS分流");
	return 0;
}

int NetFixTool() {
	Reset();
	printf("\nDNS解析服务器已成功恢复初始设置！\n\n");
	system("pause");
	return 0;
}

int Reset() {
	ResetDNSRoute();
	system("taskkill /f /im AdGuardHome.exe");
	system("del AdGuardHome.yaml");
	system("rmdir /s/q data");
	system("rmdir /s/q agh-backup");
	system("netsh interface ip set dns \"以太网\" dhcp");
	system("netsh interface ipv6 set dns \"以太网\" dhcp");
	system("netsh interface ip set dns \"WLAN\" dhcp");
	system("netsh interface ipv6 set dns \"WLAN\" dhcp");
	system("ipconfig /flushdns");
Menu3:system("cls");
	printf("检测到计算机上存在的网络适配器：\n\n");
	printf("---------------------------------------------------\n");
	system("ipconfig /all >adapter.list &type adapter.list | find \"适配器\"");
	printf("---------------------------------------------------\n");
	printf("\n已自动恢复“以太网”“WLAN”适配器设置，如需恢复其它适配器，请输入适配器名称，如以太网2，不需要则直接输入x并按回车：\n\n");
	scanf("%s", Adapter);
	if (Adapter[0] == 'x'|| Adapter[0] == 'X') {
		system("del adapter.list");
		return 0;
	}
	else {
		sprintf(Command, "netsh interface ip set dns %s dhcp", Adapter);
		system(Command);
		sprintf(Command, "netsh interface ipv6 set dns %s dhcp", Adapter);
		system(Command);
		goto Menu3;
	}
}

int ChangeVPNRoute()
{
	if ((AddRouteRules = fopen("AddRouteRules.txt", "r") != NULL)) {
		system("rundll32.exe cmroute.dll,SetRoutes /STATIC_FILE_NAME AddRouteRules.txt /DONT_REQUIRE_URL /IPHLPAPI_ACCESS_DENIED_OK");
		return 0;
	}
	else {
		printf("未找到AddRouteRules.txt文件，请前往软件主页下载后使用！\n");
		return 1;
	}
}




int ResetVPNRoute()
{
	if ((DelRouteRules = fopen("DelRouteRules.txt", "r") != NULL)) {
		system("rundll32.exe cmroute.dll,SetRoutes /STATIC_FILE_NAME DelRouteRules.txt /DONT_REQUIRE_URL /IPHLPAPI_ACCESS_DENIED_OK");
		return 0;
	}
	else {
		printf("未找到DelRouteRules.txt文件，请前往软件主页下载后使用！\n");
		return 1;
	}
}

int RunLocalDNSServer() {
	printf("正在初始化. . .\n\n");
	system("netsh interface ip set dns \"以太网\" dhcp");
	system("netsh interface ipv6 set dns \"以太网\" dhcp");
	system("netsh interface ip set dns \"WLAN\" dhcp");
	system("netsh interface ipv6 set dns \"WLAN\" dhcp");
	system("ipconfig /flushdns");
	printf("\n正在准备配置文件. . .\n\n");
	system("copy /y index.yaml AdGuardHome.yaml");
	printf("\n正在部署DNS解析服务器. . .\n\n");
	system("start "" /min AdGuardHome.exe");
	printf("正在将DNS解析服务器设置为本地解析（可能会有报错，忽略即可）. . .\n\n");
	system("netsh interface ip set dns \"以太网\" static 127.0.0.1");
	system("netsh interface ipv6 set dns \"以太网\" static ::1");
	system("netsh interface ip set dns \"WLAN\" static 127.0.0.1");
	system("netsh interface ipv6 set dns \"WLAN\" static ::1");
	system("ipconfig /flushdns");
	system("cls");
	printf("准备验证DNS，请耐心等待5s，不要退出. . .\n\n");
	system("TIMEOUT /T 1 /NOBREAK");
	printf("\n正在进行DNS解析检测. . .\n\n");
	printf("正在检测国内网站. . .\n\n");
	printf("正在检测百度解析情况. . .\n\n");
	system("nslookup www.baidu.com 127.0.0.1");
	printf("正在检测腾讯解析情况. . .\n\n");
	system("nslookup www.qq.com 127.0.0.1");
	printf("正在检测英雄联盟解析情况. . .\n\n");
	system("nslookup lol.qq.com 127.0.0.1");
	printf("正在检测王者荣耀解析情况. . .\n\n");
	system("nslookup pvp.qq.com 127.0.0.1");
	printf("正在检测境外网站. . .\n\n");
	printf("正在检测谷歌解析情况. . .\n\n");
	system("nslookup www.google.com 127.0.0.1");
	printf("正在检测油管解析情况. . .\n\n");
	system("nslookup www.youtube.com 127.0.0.1");
	printf("正在检测脸书解析情况. . .\n\n");
	system("nslookup www.facebook.com 127.0.0.1");
	printf("正在检测推特解析情况. . .\n\n");
	system("nslookup twitter.com 127.0.0.1");
	printf("正在检测Twitch解析情况. . .\n\n");
	system("nslookup www.twitch.tv 127.0.0.1");
	printf("已完成所有DNS解析的检测！\n\n");
Menu2:system("cls");
	printf("-------------------------------------------------------------------------------------\n");
	printf("-----------------------------------DNS部署成功！-------------------------------------\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("注意：使用防污染DNS期间请不要关闭本窗口及其弹出窗口，后台最小化即可！！！\n");
	printf("如需停止DNS解析请不要直接关闭窗口，否则会导致无法上网！！！\n");
	printf("如果不小心关闭本软件，可以重新打开本软件恢复默认DNS！！！\n");
	printf("-------------------------------------------------------------------------------------\n\n");
	printf("检测到计算机上存在的网络适配器：\n");
	printf("---------------------------------------------------\n");
	system("ipconfig /all >adapter.list &type adapter.list | find \"适配器\"");
	printf("---------------------------------------------------\n");
	printf("\n软件已默认配置了\"以太网\"\"WLAN\"适配器上的DNS，如需在其他适配器上配置本地DNS，请输入适配器名称，如\"以太网2\"\n");
	printf("如需关闭本地DNS并恢复默认DNS设置，请直接输入x并按回车：");
	scanf("%s",Adapter);
	if (Adapter[0] == 'x'|| Adapter[0] == 'X') {
		Reset();
		printf("\nDNS解析服务器已成功恢复初始设置！\n\n");
		return 0;
	}
	else {
		sprintf(Command, "netsh interface ip set dns %s static 127.0.0.1",Adapter);
		system(Command);
		sprintf(Command, "netsh interface ip set dns %s static ::1",Adapter);
		system(Command);
		system("ipconfig /flushdns");
		goto Menu2;
	}
	}
	

int ConfigEditor() {
	printf("请选择修改方式：\n\n1.图形界面（用户名与密码默认均为root）\n\n2.记事本\n\n请输入：");
	scanf("%d", &fixmode);
	if (fixmode == 2) {
		if ((yaml = fopen("index.yaml", "r")) == NULL) {
			Config_gen();
		}
		system("copy /y index.yaml index.yaml.bak");
		system("notepad.exe index.yaml");
		printf("\n请在弹出窗口中修改配置文件后，");
		system("pause");
	}
	else {
		printf("正在准备配置文件. . .\n\n");
		system("copy /y index.yaml index.yaml.bak");
		system("copy /y index.yaml AdGuardHome.yaml");
		printf("正在部署DNS解析服务器. . .\n\n");
		system("start "" /min AdGuardHome.exe");
		system("explorer.exe http://127.0.0.1");
		printf("\n请在弹出窗口中修改配置文件后，");
		system("pause");
		system("taskkill /f /im AdGuardHome.exe");
		system("copy /y AdGuardHome.yaml index.yaml");
		system("del AdGuardHome.yaml");
		system("rmdir /s/q data");
		system("rmdir /s/q agh-backup");
	}
	return 0;
}

int ConfigToDefault() {
	if ((bak = fopen("index.yaml.bak", "r") != NULL)){
		printf("软件目录中找到上次的配置备份，请选择恢复模式：\n\n1.恢复到上一次的配置\n\n2.恢复初始状态\n\n请输入：");
		scanf("%d", &fixmode);
		if (fixmode == 1) {
			system("copy /y index.yaml.bak index.yaml");
			printf("\n已成功恢复到上一次的配置！\n");
			return 0;
		}
	}
	system("cls");
	Config_gen();
	printf("\n已成功恢复初始状态！\n");
	system("pause");
	return 0;
}

int NSTool() {
	Boot();
	printf("正在初始化. . .\n\n");
	printf("\n正在准备配置文件. . .\n\n");
	system("copy /y index.yaml AdGuardHome.yaml");
	printf("\n正在部署DNS解析服务器. . .\n\n");
	system("start "" /min AdGuardHome.exe");
	system("ipconfig /flushdns");
	NSMenu:system("cls");
	printf("请输入要查询的域名,返回上一级请输入@：\n");
	scanf("%s",domain );
	if (domain[0] == '@') {
		system("taskkill /f /im AdGuardHome.exe");
		system("del AdGuardHome.yaml");
		system("rmdir /s/q data");
		system("rmdir /s/q agh-backup");
		return 0;
	}
	else {
		sprintf(NSCommand, "nslookup %s 127.0.0.1", domain);
		printf("\n以下为无污染DNS解析结果：\n\n");
		system(NSCommand);
		system("pause");
		goto NSMenu;
	}
	return 0;
}

int Help() {
	printf("正在打开在线帮助. . .\n");
	system("explorer https://hxhgts.github.io/AntiDNSPollute/");
	return 0;
}

int Boot() {
	mode = 0;
	system("taskkill /f /im AdGuardHome.exe");
	system("del AdGuardHome.yaml");
	system("rmdir /s/q data");
	system("rmdir /s/q agh-backup");
	if ((AdGuardHome = fopen("AdGuardHome.exe", "r")) == NULL) {
		return 1;
	}
	else {
		if ((yaml = fopen("index.yaml", "r")) == NULL) {
			Config_gen();
			printf("模式2配置文件已生成！\n\n");
			system("pause");
		}
		return 0;
	}
}

int FixHosts() {
	printf("正在恢复默认Hosts文件. . .\n\n");
	SystemHosts = fopen("hosts", "w");
	fprintf(SystemHosts, "");
	fclose(SystemHosts);
	system("del %windir%\\System32\\drivers\\etc\\hosts");
	system("copy /y hosts %windir%\\System32\\drivers\\etc\\hosts");
	system("del hosts");
	system("ipconfig /flushdns");
	printf("\n已成功恢复默认Hosts文件！\n\n");
	system("pause");
	system("cls");
	return 0;
}

int Checkdll() {
	dll = fopen("cmroute.dll", "r");
	if (dll != NULL) {
		return 0;
	}
	else {
		return 1;
	}
}

int ChangeDNSRoute() {
	AddDNSRoutes = fopen("AddDNSRoutes.txt", "w");
	fprintf(AddDNSRoutes, "add 1.0.0.1 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 1.1.1.1 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 8.8.8.8 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 8.8.4.4 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 9.9.9.9 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 208.67.220.220 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 208.67.220.222 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 208.67.222.220 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 208.67.222.222 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 146.112.41.2 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 115.159.131.230 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 149.112.112.112 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 176.103.130.130 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 176.103.130.131 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 130.59.31.251 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(AddDNSRoutes, "add 130.59.31.248 mask 255.255.255.255 default METRIC default IF default\n");
	fclose(AddDNSRoutes);
	system("rundll32.exe cmroute.dll,SetRoutes /STATIC_FILE_NAME AddDNSRoutes.txt /DONT_REQUIRE_URL /IPHLPAPI_ACCESS_DENIED_OK");
	system("del AddDNSRoutes.txt");
	return 0;
}

int ResetDNSRoute() {
	DelDNSRoutes = fopen("DelDNSRoutes.txt", "w");
	fprintf(DelDNSRoutes, "delete 1.0.0.1 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 1.1.1.1 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 8.8.8.8 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 8.8.4.4 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 9.9.9.9 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 208.67.220.220 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 208.67.220.222 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 208.67.222.220 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 208.67.222.222 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 146.112.41.2 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 115.159.131.230 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 149.112.112.112 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 176.103.130.130 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 176.103.130.131 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 130.59.31.251 mask 255.255.255.255 default METRIC default IF default\n");
	fprintf(DelDNSRoutes, "delete 130.59.31.248 mask 255.255.255.255 default METRIC default IF default\n");
	fclose(DelDNSRoutes);
	system("rundll32.exe cmroute.dll,SetRoutes /STATIC_FILE_NAME DelDNSRoutes.txt /DONT_REQUIRE_URL /IPHLPAPI_ACCESS_DENIED_OK");
	system("del DelDNSRoutes.txt");
	return 0;
}

int UserInterface() {
	printf("请选择DNS服务器运行方式：\n\n1.运行国内外分流+本地DNS\n\n2.运行本地DNS（仅启动DNS）\n\n3.全局类VPN软件分流\n\n4.重置DNS（运行本地DNS时未正常退出，可用此选项恢复上网功能）\n\n5.自定义DNS配置文件（用于添加自定义上游）\n\n6.重置配置文件（自定义失败时可用于恢复默认，用户名密码也将被重置）\n\n7.无污染DNS解析结果获取（不修改本机DNS，仅输出结果）\n\n8.重置系统Hosts文件\n\n9.在线帮助\n\n0.退出\n\n请输入：");
	scanf("%d", &mode);
	system("cls");
	return 0;
}