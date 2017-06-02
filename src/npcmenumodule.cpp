#include "npcmenumodule.h"
#include "npc.h"
#include "hitarea.h"
#include "controller.h"
#include "talentdata.h"
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>

NPCMenuModule::NPCMenuModule()
{
    nameLabel = new QLabel();
    nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    viewButton = new QPushButton("More Info");
    connect(viewButton, SIGNAL(clicked(bool)), this, SLOT(on_viewEvent()));

    npc = new NPC();
}

NPCMenuModule::~NPCMenuModule()
{
    delete nameLabel;
    delete viewButton;
    delete npc;
}

void NPCMenuModule::addWidgets()
{
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(viewButton, 1, 0);
    layout->addWidget(del, 2, 0);
}

NPC* NPCMenuModule::getNPC()
{
    QVector<HitArea>* areas = new QVector<HitArea>();

    int r = 0;
    while (layout->itemAtPosition(r, 1))
    {
        QWidget* w = layout->itemAtPosition(r, 1)->widget();
        QLabel* name = dynamic_cast<QLabel*>(w);

        if (name)
        {
            HitArea area = HitArea();
            area.setName(name->text());

            QVector<int> values = QVector<int>();
            int c = 2;
            while (layout->itemAtPosition(r, c))
            {
                QWidget* w2 = layout->itemAtPosition(r, c)->widget();
                QCheckBox* check = dynamic_cast<QCheckBox*>(w2);

                if (check)
                {
                    int i = TalentData::stateToInt(check->checkState());
                    values.append(i);
                }

                c++;
            }
            area.setValues(values);
            areas->append(area);
        }

        r++;
    }

    npc->setHitAreas(areas);

    return npc;
}

void NPCMenuModule::setNPC(NPC* newNPC)
{
    if (npc) delete npc;
    npc = new NPC(newNPC);

    QVector<QWidget*> killList = QVector<QWidget*>();
    for (int i = 0; i < layout->count(); i++)
    {
        int r;
        int c;
        int rSpan;
        int cSpan;
        layout->getItemPosition(i, &r, &c, &rSpan, &cSpan);

        if (c > 0)
        {
            killList.append(layout->itemAt(i)->widget());
        }
    }
    foreach (QWidget* w, killList)
    {
        layout->removeWidget(w);
        delete w;
    }

    nameLabel->setText(npc->getName());
    setDeleteText("Remove");
    setIdentifier(npc->getName());

    int r = 0;
    foreach (HitArea area, *npc->getHitAreas())
    {
        QLabel* name = new QLabel(area.getName());
        layout->addWidget(name, r, 1);

        int c = 2;
        foreach (int i, area.getValues())
        {
            QCheckBox* box = new QCheckBox();
            box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            box->setTristate(true);
            box->setCheckState(TalentData::intToState(i));
            layout->addWidget(box, r, c);
            connect(box, SIGNAL(clicked(bool)), this, SLOT(on_update()));
            c++; //Would you look at that.
        }

        r++;
    }
}

void NPCMenuModule::on_viewEvent()
{
    emit viewNPC(npc);
}
