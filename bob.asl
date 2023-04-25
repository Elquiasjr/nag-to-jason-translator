Agent bob {
	Beliefs {
		estaChovendo
		naotenhoGuardaChuva
	}
	Goals {
		comprarGuardaChuva
		naoPegarChuva
	}
	Plans {
		Plan plano1 {
			TriggerEvent comprarGuardaChuva
			Context estaChovendo E naotenhoGuardaChuva
			Body {
				sair
				procurarLoja
				comprarGuardaChuva
			}
		}
		Plan plano2 {
			TriggerEvent naoPegarChuva
			Context NAO estaChovendo
			Body {
				sair
				jogarBola
			}
		}
		Plan plano3 {
			TriggerEvent naoPegarChuva
			Context estaChovendo E naotenhoGuardaChuva
			Body {
				ficarEmCasa
				estudar
			}
		}
	}
}
