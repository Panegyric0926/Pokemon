﻿#include "pokemondlg.h"
#include "ui_pokemondlg.h"
#include <QVBoxLayout>

PokemonDlg::PokemonDlg(const QString &detail, bool myPokemonTable, QWidget *parent) : QDialog(parent),
																																											ui(new Ui::PokemonDlg)
{
	ui->setupUi(this);

	// ui
    setWindowTitle(tr(u8"精灵详情"));
	table = new QTableWidget(this);
	table->setColumnCount(1);
	table->setRowCount(9);
    table->setVerticalHeaderLabels({tr(u8"精灵ID"), tr(u8"名字"), tr(u8"种族"), tr(u8"攻击力"), tr(u8"防御力"), tr(u8"生命值"), tr(u8"速度"), tr(u8"等级"), tr(u8"经验")});
    //table->horizontalHeader()->hide();
    //table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// data
	auto details = detail.split(' ');
	for (int i = 0; i < 9; ++i)
	{
		auto t = new QTableWidgetItem(details[i]);

		if (i != 1)
		{
			// only pokemon name can be changed
			t->setFlags(t->flags() ^ Qt::ItemIsEnabled);
			t->setBackgroundColor(QColor("#eff0f1"));
		}
		else
		{
			if (myPokemonTable)
			{
                t->setToolTip(tr(u8"双击以更改精灵名称"));
			}
			else
			{
				// can not change other players' pokemons' name
				t->setFlags(t->flags() ^ Qt::ItemIsEditable);
				t->setBackgroundColor(QColor("#eff0f1"));
			}
		}
		table->setItem(i, 0, t);
	}
	connect(table, &QTableWidget::cellChanged, this, [this, detail] { emit pokemonChangeName(detail[0], table->item(1, 0)->text()); });

	// img
	lbImg = new QLabel(this); // name
    if (details[2] == "Bulbasaur")
	{
		lbImg->setPixmap(QPixmap(":/img/img/bulbasaur.png"));
		setWindowIcon(QIcon(":/img/img/bulbasaur.png"));
	}
    else if (details[2] == "Charmander")
	{
		lbImg->setPixmap(QPixmap(":/img/img/charmander.png"));
		setWindowIcon(QIcon(":/img/img/charmander.png"));
	}
    else if (details[2] == "Squirtle")
	{
		lbImg->setPixmap(QPixmap(":/img/img/squirtle.png"));
		setWindowIcon(QIcon(":/img/img/squirtle.png"));
	}
    else if (details[2] == "Pikachu")
	{
        lbImg->setPixmap(QPixmap(":/img/img/pikachu.png"));
        setWindowIcon(QIcon(":/img/img/pikachu.png"));
	}

	// layout
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(lbImg, 0, Qt::AlignCenter);
	layout->addWidget(table, 0, Qt::AlignHCenter);
	setLayout(layout);
	setFixedSize(340, 670); // can not resize window

	// memory
	setAttribute(Qt::WA_DeleteOnClose);

	// setup ui after data filling
	setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
	show();
}

PokemonDlg::~PokemonDlg()
{
	delete ui;
}
