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

NPCMenuModule::NPCMenuModule() : MenuModule()
{
    nameLabel = new QLabel();
    nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    viewButton = new QPushButton("More Info");
    connect(viewButton, SIGNAL(clicked(bool)), this, SLOT(on_viewEvent()));

    hitLayout = new QGridLayout();

    npc = new NPC();
}

NPCMenuModule::~NPCMenuModule()
{
    delete nameLabel;
    delete viewButton;
    delete npc;
    delete hitLayout;
}

void NPCMenuModule::addWidgets()
{
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(viewButton, 1, 0);
    layout->addWidget(del, 2, 0);
    layout->addLayout(hitLayout, 0, 1);
}

NPC* NPCMenuModule::getNPC()
{
    QVector<HitArea>* areas = new QVector<HitArea>();

    int r = 0;
    while (hitLayout->itemAtPosition(r, 0))
    {
        QWidget* w = hitLayout->itemAtPosition(r, 0)->widget();
        QLabel* name = dynamic_cast<QLabel*>(w);

        if (name)
        {
            HitArea area = HitArea();
            area.setName(name->text());

            QVector<int> values = QVector<int>();
            int c = 1;
            while (hitLayout->itemAtPosition(r, c))
            {
                QWidget* w2 = hitLayout->itemAtPosition(r, c)->widget();
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

    while (hitLayout->count() > 0)
    {
        QWidget* w = hitLayout->itemAt(0)->widget();
        hitLayout->removeWidget(w);
        delete w;
    }

    nameLabel->setText(npc->getName());
    setDeleteText("Remove");
    setIdentifier(npc->getName());

    int r = 0;
    foreach (HitArea area, *npc->getHitAreas())
    {
        QLabel* name = new QLabel(area.getName());
        hitLayout->addWidget(name, r, 0);

        int c = 1;
        foreach (int i, area.getValues())
        {
            QCheckBox* box = new QCheckBox();
            box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            box->setTristate(true);
            box->setCheckState(TalentData::intToState(i));
            hitLayout->addWidget(box, r, c);
            connect(box, SIGNAL(clicked(bool)), this, SLOT(on_update()));
            c++; //Would you look at that.
        }

        r++;
    }

    int rows = hitLayout->rowCount();
    layout->removeItem(hitLayout);
    layout->addLayout(hitLayout, 0, 1, rows, 1);
}

void NPCMenuModule::on_viewEvent()
{
    emit viewNPC(npc);
}
