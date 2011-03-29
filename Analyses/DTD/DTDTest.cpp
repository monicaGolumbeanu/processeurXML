#include <XMLTag.h>
#include <XMLPCDATA.h>
#include <DTD.h>
#include <DTDElement.h>
#include <DTDRule.h>
#include <DTDRuleFinal.h>
#include <DTDRuleAtomic.h>
#include <DTDRuleChoice.h>
#include <DTDRuleSequence.h>
#include <XMLValidateWithDTDVisitor.h>
#include <DTDTest.h>

void DTDTest() {
    //Árvore
    XMLTag* html = new XMLTag("html");
    XMLTag* head = new XMLTag("head");
    XMLTag* body = new XMLTag("body");
    body->addChild(new XMLPCDATA("It works!"));
    XMLTag* title = new XMLTag("title");
    //title->addChild(new XMLPCDATA("BLA!!"));
    head->addChild(title);
    html->addChild(body);
    html->addChild(head);
    //Regras
    DTD* dtd = new DTD();
    DTDElement* html_element = new DTDElement("html");
    DTDElement* head_element = new DTDElement("head");
    DTDElement* body_element = new DTDElement("body");
    DTDElement* title_element = new DTDElement("title");
    DTDElement* link_element = new DTDElement("link");
    DTDElement* meta_element = new DTDElement("meta");
    dtd->addElement(html_element);
    dtd->addElement(head_element);
    dtd->addElement(body_element);
    dtd->addElement(title_element);
    dtd->addElement(link_element);
    dtd->addElement(meta_element);
    DTDRuleAtomic* rule_title = new DTDRuleAtomic();
    rule_title->setRule(new DTDRuleFinal());
    DTDRuleAtomic* rule_meta = new DTDRuleAtomic();
    rule_meta->setRule(new DTDRuleFinal());
    DTDRuleAtomic* rule_link = new DTDRuleAtomic();
    rule_link->setRule(new DTDRuleFinal());
    DTDRuleAtomic* rule_body = new DTDRuleAtomic();
    rule_body->setRule(new DTDRuleFinal());
    title_element->setRule(rule_title);
    link_element->setRule(rule_link);
    meta_element->setRule(rule_meta);
    body_element->setRule(rule_body);
    DTDRuleChoice* rule_head = new DTDRuleChoice();
    rule_head->addRule(rule_title);
    rule_head->addRule(rule_link);
    rule_head->addRule(rule_meta);
    head_element->setRule(rule_head);
    DTDRuleSequence* rule_html = new DTDRuleSequence();
    rule_html->addRule(rule_head);
    rule_html->addRule(rule_body);
    html_element->setRule(rule_html);
    try {
        dtd->validate(head);
        cout << "VALID!" << endl;
    }
    catch(...) {
        cout << "NOT VALID!" << endl;
    }
}
