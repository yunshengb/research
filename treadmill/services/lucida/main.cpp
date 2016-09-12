#include "User.h"
#include <iostream>
#include <stdexcept>

#include <htmlcxx/html/ParserDom.h>

using namespace std;
using namespace htmlcxx;

int main() {
  try {
    User user("demo1", "cookies1");
    user.sendLoginRequest();
    user.sendLearnImageRequest();
    user.sendInferImageRequest();
    user.sendLearnTextRequest();
    user.sendLearnUrlRequest();
  } catch (const runtime_error &e) {
    cout << e.what() << "\n";
  }



  // //Parse some html code
  // string html = "<html><body>hey</body></html>";
  // HTML::ParserDom parser;
  // tree<HTML::Node> dom = parser.parseTree(html);
  
  // //Print whole DOM tree
  // cout << dom << endl;
  
  // //Dump all links in the tree
  // tree<HTML::Node>::iterator it = dom.begin();
  // tree<HTML::Node>::iterator end = dom.end();
  // for (; it != end; ++it)
  // {
  //   if (it->tagName() == "A")
  //   {
  //     it->parseAttributes();
  //     cout << it->attribute("href").second;
  //   }
  // }
  
  // //Dump all text of the document
  // it = dom.begin();
  // end = dom.end();
  // for (; it != end; ++it)
  // {
  //   if ((!it->isTag()) && (!it->isComment()))
  //   {
  //     cout << it->text();
  //   }
  // }

    return 0;
}
