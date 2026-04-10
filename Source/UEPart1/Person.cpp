// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	// 기본 값 설정.
	Name = TEXT("홍길동");
	Year = 1;

	// 카드 객체 생성.
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card")); // 유일한 값을 넣는게 좋다.
}
