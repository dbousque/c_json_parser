

#include "json.h"

int		main(int argc, char **argv)
{
	t_value	*json;

	if (argc > 1)
	{
		json = read_json(argv[1]);
		(void)json;
	}
	return (0);
}