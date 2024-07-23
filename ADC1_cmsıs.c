void ADC_Init(void)
{
	SYSCFG->PMCR |= SYSCFG_PMCR_PA1SO;
    GPIOA->MODER |= GPIO_MODER_MODE1;
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD1);

	RCC->AHB1ENR |= RCC_AHB1ENR_ADC12EN;
	ADC12_COMMON->CCR |= ADC_CCR_CKMODE_1;
	
	ADC1->CFGR |=ADC_CFGR_CONT;
	ADC1->PCSEL_RES0 |= ADC_PCSEL_PCSEL_1;
    ADC1->SQR1 |= ADC_SQR1_SQ1_0;
    ADC1->CR |= ADC_CR_BOOST_1;
	ADC1->SMPR1 |= 0x00000030;
	
	ADC1->CR &= ~(ADC_CR_DEEPPWD);

    ADC1->CR |= ADC_CR_ADVREGEN;
    while (!( ADC1->ISR & ADC_ISR_LDORDY))
	for (int i = 0; i<10000; i++){};

	ADC1->ISR |= ADC_ISR_ADRDY;
    ADC1->CR |=ADC_CR_ADEN;
    for( uint32_t x=0 ; x<7; x++) ;
}



uint16_t ADC_Read(void)
{
	uint16_t adc_dr;

	ADC1->ISR |= ADC_ISR_EOC;

	ADC1->CR |=ADC_CR_ADSTART;
	while (!( ADC1->ISR & ADC_ISR_EOC))

	adc_dr = ADC1->DR;

	ADC1->CR |=ADC_CR_ADSTP;

	return adc_dr;
}
