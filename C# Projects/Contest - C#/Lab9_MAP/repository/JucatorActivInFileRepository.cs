using System;
using System.Collections.Generic;
using System.Text;
using Lab9_MAP.model;
using Lab9_MAP.validator;

namespace Lab9_MAP.repository
{
    class JucatorActivInFileRepository : InFileRepository<string, JucatorActiv>
    {
        public JucatorActivInFileRepository(IValidator<JucatorActiv> validator, string filename) : base(validator, filename, EntityToFileMapping.CreateJucatorActiv) { }
    }
}
