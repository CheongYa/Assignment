using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonExample_UC
{
    public class Card
    {
        public string category;
        public string number;
        public string name;
        public List<string> forward = new List<string>();
        public List<string> reverse = new List<string>();
        public int degree;
    }
}
