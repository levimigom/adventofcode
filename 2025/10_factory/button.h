struct Button {
	int *lights, light_count;
};

void button_print(struct Button *button){
	int i;

	printf("\tButton (%d lights): ", button->light_count);
	for(i = 0; i < button->light_count; i++){
		printf("%d, ", button->lights[i]);
	}
	printf("\n");
}

struct Button *button_create(char *s){
	struct Button *button = malloc(sizeof(struct Button));
	button->light_count = 1;	
	button->lights = calloc(sizeof(int), 1);

	int i;

	for(i = 1; s[i + 1] != '\0'; i++){
		if(s[i] == ','){
			button->light_count += 1;
			button->lights = realloc(button->lights, sizeof(int) * button->light_count);
			button->lights[button->light_count - 1] = 0;
		} else {
			button->lights[button->light_count - 1] *= 10;
			button->lights[button->light_count - 1] += s[i] - '0';
		}
	}

	return button;
}

void button_free(struct Button *button){
	free(button->lights);
	free(button);
}