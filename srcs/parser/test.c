char	**get_commands(char *s);

int main()
{
	get_commands("    'e'c'h'o     kek");
	get_commands(" 'e'c';h'o   kek");
	get_commands("echo kek; echo kek2");
	get_commands("'e'c'h'o kek lel 123 456");
	get_commands("'e'c'h'o kek lel      123 456");
	get_commands("\"echo  \" kek lel      123 456");
	get_commands("echo echo | cat -e");
	return (0);
}
