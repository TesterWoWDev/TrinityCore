UPDATE `access_requirement` SET `quest_done_A`=10277, `quest_done_H`=10277, `quest_failed_text`="You must complete the quest ""The Caverns of Time"" before entering Old Hillsbrad Foothills" WHERE `MapID` IN (560) AND `difficulty`=0;
UPDATE `access_requirement` SET `quest_done_A`=10277, `quest_done_H`=10277, `quest_failed_text`="You must complete the quest ""The Caverns of Time"" and be level 70 before entering the Heroic difficulty of Old Hillsbrad Foothills" WHERE `MapID` IN (560) AND `difficulty`=1;