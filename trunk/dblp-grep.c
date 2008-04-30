#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>

xmlDocPtr doc;
xmlNodePtr root;

char authors[512];
char year[32];
char conf[32];
char title[1024];

char *g_conf;

void parseNode(xmlNodePtr node)
{
	xmlNodePtr child = NULL;
	char *name = NULL;
	char *value = NULL;

	name = (char *)node->name;
	value = (char *)xmlNodeListGetString(doc, node->xmlChildrenNode, 1);

	//sprintf((char *)value, "%s", xmlNodeListGetString(doc, node->xmlChildrenNode, 1));
	//printf(":%s\n", xmlNodeListGetString(doc, node->xmlChildrenNode, 1));

	if (!strcmp(name, "inproceedings") || !strcmp(name, "dblp")) {
		memset(authors, 0, 1024);
		memset(year, 0, 32);
		memset(conf, 0, 32);
		memset(title, 0, 32);
		//printf("This is inproceedings.\n");

		child = node->xmlChildrenNode;
		while (child != NULL) {
			parseNode(child);
			child = child->next;
		}

		if (!strcmp(conf, g_conf)) {
			printf("%s\t%s\t%s\t%s\n", conf, year, title, authors);
		}
	} else if (!strcmp(name, "author")) {
		return;
	} else if (!strcmp(name, "year")) {
		strcpy(year, value);
	} else if (!strcmp(name, "title")) {
		strcpy(title, value);
	} else if (!strcmp(name, "booktitle")) {
		strcpy(conf, value);
	}

	//printf("%s:%s\n", name, value);
}

bool loadXml(char *filename)
{
	doc = xmlParseFile(filename);
	if (doc == NULL)
		return false;
	root = xmlDocGetRootElement(doc);
	if (root == NULL)
		return false;
	parseNode(root);
	return true;
}

int main(int argc, char **argv)
{
	if (argc == 1)
		return -1;
	g_conf = strdup(argv[1]);
	loadXml(argv[2]);
}
