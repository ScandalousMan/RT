#include <rt.h>

t_light	*light_copy(t_light *src)
{
	t_light	*copy;

	if (!src)
		return (NULL);
	if (!(copy = duplicate(src, sizeof(t_light))))
		return (NULL);
	if (src->next)
	{
		if (!(copy->next = light_copy(src->next)))
			return (NULL);
	}
	return (copy);
}

t_object	*light_masked(t_param *param, double *from, double *to, t_path *path)
{
	param->intersect_object = NULL;
	param->is_for_light = 1;
	closest_object(param, from, path->l, path);
	if (param->obj_d * param->obj_d > pt_dist_root(from, param->tmp_light->src))
		param->intersect_object = NULL;
	if (param->i[0] == 390 && param->i[1] == 397) {
		printf(" end light: %s\n=========\n\n", param->intersect_object ? "masked" : "illuminated");
	}
	return (param->intersect_object);
}
