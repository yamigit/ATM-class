using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ATM
{
    class PeopleInfo
    {
        private string account;
        private string name;
        private string ID;
        private string passsword;

        public string Account
        {
            get
            {
                return account;
            }

            set
            {
                account = value;
            }
        }

        public string Name
        {
            get
            {
                return name;
            }

            set
            {
                name = value;
            }
        }
    }
}
