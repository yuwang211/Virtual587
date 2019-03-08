#include <cstdio>
#include <cstring>
#include <string>
#include <map>

class Token{
	
	public:
	
		Token();
	
		void init(std::string fn);
		
		bool getNext(std::string &s);
		
		~Token();
		
	private:
	
		static const int LEN_CACHE = 10000;
		
		FILE *fin;
		char *cache;
		int line, pos, len;
		
		bool flag;
};

Token::Token()
{
	fin = NULL;
	cache = NULL;
}

Token::~Token()
{
	if (!cache) free(cache);
}

void Token::init(std::string fn)
{
	fin = fopen(fn.c_str(), "r");
	cache = (char *)malloc(sizeof(char) * LEN_CACHE);
	flag = false;
	pos = len = line = 0;
}

bool Token::getNext(std::string &s)
{
	if (flag) return false;
	while (pos < len && (cache[pos] <= ' ')) ++pos;
    while (pos >= len)
	{
		if (!fgets(cache, LEN_CACHE, fin))
		{
			flag = true;
			return false;
		}
		++line;
		len = strlen(cache);
		pos = 0;
		while (pos < len && (cache[pos] <= ' ')) ++pos;
	}
	if (('A' <= cache[pos] && cache[pos] <= 'Z') || 
	    ('a' <= cache[pos] && cache[pos] <= 'z') || 
		(cache[pos] == '_'))
	{
		s = "";
		s = s + cache[pos++];
		while ((pos < len) &&
     		   (('A' <= cache[pos] && cache[pos] <= 'Z') || 
	           ('a' <= cache[pos] && cache[pos] <= 'z') || 
	           ('0' <= cache[pos] && cache[pos] <= '9') || 
		       (cache[pos] == '_')))
		{
			s = s + cache[pos++];
		}
		return true;
	}
	else if ('0' <= cache[pos] && cache[pos] <= '9')
	{
		s = "";
		s = s + cache[pos++];
		while ((pos < len) &&
     		   (('0' <= cache[pos] && cache[pos] <= '9') || 
		       (cache[pos] == '.')))
		{
			s = s + cache[pos++];
		}
		return true;
	}
	else
	{
		if ((pos + 1 < len) && (cache[pos + 1] == '=') && 
		    ((cache[pos] == '=') ||
		    (cache[pos] == '!') ||
			(cache[pos] == '<') ||
			(cache[pos] == '>')))
		{
			s = "";
			s = s + cache[pos++];
			s = s + cache[pos++];
			return true;
		}
		else
		{
			s = "";
			s = s + cache[pos++];
			return true;
		}
	}
}




int main()
{
	Token t;
	t.init("in.txt");
	std::string s;
	while (t.getNext(s))
	{
		printf("[%s]\n", s.c_str());
	}
	return 0;
}