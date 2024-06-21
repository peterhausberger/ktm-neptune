struct {
	ads7883_instance_t cs0;
	ads7883_instance_t cs1;
} ads2 = {
	{.spi_instance = &spi_2, .spi_device = &spi_2_cs_0}, 
	{.spi_instance = &spi_2, .spi_device = &spi_2_cs_1}
};

int32_t ads2_init(void) {
    ads7883_init(&ads2.cs0);
	ads7883_init(&ads2.cs1);
	return 0;
}

int32_t ads2_deinit(void) {
	ads7883_deinit(&ads2.cs1);
    ads7883_deinit(&ads2.cs0);
	return 0;
}

int32_t ads2_step(void) {
    ads7883_step(&ads2.cs0);
	ads7883_step(&ads2.cs1);

	if (scheduler0.cycle % 2 == 0) {
		ads7883_start_conversion(&ads2.cs0);
	} else {
		ads7883_start_conversion(&ads2.cs1);
	}

    return 0;
}
