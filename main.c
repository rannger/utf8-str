#include <stdio.h>
#include "utf8_str.h"

int main(int argc,char* argv[])
{
		char str[] =	"猗与那与！置我鞉鼓。"
						"奏鼓简简，衎我烈祖。"
						"汤孙奏假，绥我思成。"
						"鞉鼓渊渊，嘒嘒管声。"
						"既和且平，依我磬声。"
						"于赫汤孙！穆穆厥声。"
						"庸鼓有斁，万舞有奕。"
						"我有嘉客，亦不夷怿。"
						"自古在昔，先民有作。"
						"温恭朝夕，执事有恪，"
						"顾予烝尝，汤孙之将。";
		size_t len = sizeof(str)/sizeof(str[0]);
		utf8_char** utf8_str = rd_utf8_str(str,sizeof(str)/sizeof(str[0]));
		for (int i = 0;NULL!=utf8_str[i];i++) {
			utf8_char* ch = utf8_str[i];
			for(int j=0;j<ch->len;j++) {
					putchar(ch->data[j]);
			}
			putchar(' ');
		}
		release_utf8_str(utf8_str);
		return 0;
}
