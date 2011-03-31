#include <XMLAttr.h>
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
    //XML Tree
    XMLTag* html = new XMLTag("html");
    XMLTag* body = new XMLTag("body");
    XMLTag* head = new XMLTag("head");
    body->addChild(new XMLPCDATA("It works!"));
    XMLTag* title = new XMLTag("title");
    title->addChild(new XMLPCDATA("BLA!!"));
    head->addChild(title);
    html->addChild(head);
    html->addChild(body);
    //head->addAttr(new XMLAttr("attrQuiNexistePas"));
    //html->addChild(new XMLTag("jeNexistePas"));
    //Elements
    DTD* dtd = new DTD();
    DTDElement* html_element = new DTDElement("html");
    DTDElement* head_element = new DTDElement("head");
    DTDElement* body_element = new DTDElement("body");
    DTDElement* title_element = new DTDElement("title");
    DTDElement* link_element = new DTDElement("link");
    DTDElement* meta_element = new DTDElement("meta");
    dtd->addElement(html_element);
    dtd->addElement(body_element);
    dtd->addElement(head_element);
    dtd->addElement(title_element);
    dtd->addElement(link_element);
    dtd->addElement(meta_element);
    DTDRuleFinal* rule_title = new DTDRuleFinal();
    DTDRuleFinal* rule_meta = new DTDRuleFinal();
    DTDRuleFinal* rule_link = new DTDRuleFinal();
    DTDRuleFinal* rule_body = new DTDRuleFinal();
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
    rule_html->addRule(rule_body);
    rule_html->addRule(rule_head);
    html_element->setRule(rule_html);
    if(dtd->validate(html))
        cout << "VALID!" << endl;
    else
        cout << "INVALID!" << endl;
}
