class Rules {
  static verbs = {
//   $v1        $vs        $vg         $v2        $v3
    'catch': [ 'catches', 'catching', 'caught',  'caught'  ],
    'do':    [ 'does',    'doing',    'did',     'done'    ],
    'enter': [ 'enters',  'entering', 'entered', 'entered' ],
    'get':   [ 'gets',    'getting',  'got',     'gotten'  ],
    'have':  [ 'has',     'having',   'had',     'had'     ],
    'read':  [ 'reads',   'reading',  'read',    'read'    ],
    'ring':  [ 'rings',   'ringing',  'rang',    'rung'    ],
    'set':   [ 'sets',    'setting',  'set',     'set'     ],
    'sing':  [ 'sings',   'singing',  'sang',    'sung'    ],
    'sleep': [ 'sleeps',  'sleeping', 'slept',   'slept'   ],
    'stand': [ 'stands',  'standing', 'stood',   'stood'   ],
    'study': [ 'studies', 'studying', 'studied', 'studied' ],
    'take':  [ 'takes',   'taking',   'took',    'taken'   ],
    'work':  [ 'works',   'working',  'worked',  'worked'  ],
    'write': [ 'writes',  'writing',  'wrote',   'written' ],
  };

  static tenses = {
    'positive statement past nonPerfect simple I he she it we you they':       '$s #$v2',
    'positive statement past nonPerfect continuous I he she it':               '$s was #$vg',
    'positive statement past nonPerfect continuous we you they':               '$s were #$vg',
    'positive statement past perfect simple I he she it we you they':          '$s had #$v3',
    'positive statement past perfect continuous I he she it we you they':      '$s had #been #$vg',
    'positive statement present nonPerfect simple I we you they':              '$s #$v1',
    'positive statement present nonPerfect simple he she it':                  '$s #$vs',
    'positive statement present nonPerfect continuous I':                      '$s am #$vg',
    'positive statement present nonPerfect continuous he she it':              '$s is #$vg',
    'positive statement present nonPerfect continuous we you they':            '$s are #$vg',
    'positive statement present perfect simple I we you they':                 '$s have #$v3',
    'positive statement present perfect simple he she it':                     '$s has #$v3',
    'positive statement present perfect continuous I we you they':             '$s have #been #$vg',
    'positive statement present perfect continuous he she it':                 '$s has #been #$vg',
    'positive statement future nonPerfect simple I he she it we you they':     '$s will #$v1',
    'positive statement future nonPerfect continuous I he she it we you they': '$s will #be #$vg',
    'positive statement future perfect simple I he she it we you they':        '$s will #have #$v3',
    'positive statement future perfect continuous I he she it we you they':    '$s will #have #been #$vg',

    'positive question past nonPerfect simple I he she it we you they':        'did $s #$v1',
    'positive question past nonPerfect continuous I he she it':                'was $s #$vg',
    'positive question past nonPerfect continuous we you they':                'were $s #$vg',
    'positive question past perfect simple I he she it we you they':           'had $s #$v3',
    'positive question past perfect continuous I he she it we you they':       'had $s #been #$vg',
    'positive question present nonPerfect simple I we you  they':              'do $s #$v1',
    'positive question present nonPerfect simple he she it':                   'does $s #$v1',
    'positive question present nonPerfect continuous I':                       'am $s #$vg',
    'positive question present nonPerfect continuous he she it':               'is $s #$vg',
    'positive question present nonPerfect continuous we you they':             'are $s #$vg',
    'positive question present perfect simple I we you they':                  'have $s #$v3',
    'positive question present perfect simple he she it':                      'has $s #$v3',
    'positive question present perfect continuous I we you they':              'have $s #been #$vg',
    'positive question present perfect continuous he she it':                  'has $s #been #$vg',
    'positive question future nonPerfect simple I he she it we you they':      'will $s #$v1',
    'positive question future nonPerfect continuous I he she it we you they':  'will $s #be #$vg',
    'positive question future perfect simple I he she it we you they':         'will $s #have #$v3',
    'positive question future perfect continuous I he she it we you they':     'will $s #have #been #$vg',

    'negative statement past nonPerfect simple I he she it we you they':       '$s did not #$v1',
    'negative statement past nonPerfect continuous I he she it':               '$s was not #$vg',
    'negative statement past nonPerfect continuous we you they':               '$s were not #$vg',
    'negative statement past perfect simple I he she it we you they':          '$s had not #$v3',
    'negative statement past perfect continuous I he she it we you they':      '$s had not #been #$vg',
    'negative statement present nonPerfect simple I we you they':              '$s do not #$v1',
    'negative statement present nonPerfect simple he she it':                  '$s does not #$v1',
    'negative statement present nonPerfect continuous I':                      '$s am not #$vg',
    'negative statement present nonPerfect continuous he she it':              '$s is not #$vg',
    'negative statement present nonPerfect continuous we you they':            '$s are not #$vg',
    'negative statement present perfect simple I we you they':                 '$s have not #$v3',
    'negative statement present perfect simple he she it':                     '$s has not #$v3',
    'negative statement present perfect continuous I we you they':             '$s have not #been #$vg',
    'negative statement present perfect continuous he she it':                 '$s has not #been #$vg',
    'negative statement future nonPerfect simple I he she it we you they':     '$s will not #$v1',
    'negative statement future nonPerfect continuous I he she it we you they': '$s will not #be #$vg',
    'negative statement future perfect simple I he she it we you they':        '$s will not #have #$v3',
    'negative statement future perfect continuous I he she it we you they':    '$s will not #have #been #$vg',

    'negative question past nonPerfect simple I he she it we you they':        'did $s not #$v1',
    'negative question past nonPerfect continuous I he she it':                'was $s not #$vg',
    'negative question past nonPerfect continuous we you they':                'were $s not #$vg',
    'negative question past perfect simple I he she it we you they':           'had $s not #$v3',
    'negative question past perfect continuous I he she it we you they':       'had $s not #been #$vg',
    'negative question present nonPerfect simple I we you they':               'do $s not #$v1',
    'negative question present nonPerfect simple he she it':                   'does $s not #$v1',
    'negative question present nonPerfect continuous I':                       'am $s not #$vg',
    'negative question present nonPerfect continuous he she it':               'is $s not #$vg',
    'negative question present nonPerfect continuous we you they':             'are $s not #$vg',
    'negative question present perfect simple I we you they':                  'have $s not #$v3',
    'negative question present perfect simple he she it':                      'has $s not #$v3',
    'negative question present perfect continuous I we you they':              'have $s not #been #$vg',
    'negative question present perfect continuous he she it':                  'has $s not #been #$vg',
    'negative question future nonPerfect simple I he she it we you they':      'will $s not #$v1',
    'negative question future nonPerfect continuous I he she it we you they':  'will $s not #be #$vg',
    'negative question future perfect simple I he she it we you they':         'will $s not #have #$v3',
    'negative question future perfect continuous I he she it we you they':     'will $s not #have #been #$vg',
  };

  static contractions_negative = {
    'are( \\w+)? not':  'aren\'t$1',
    'did( \\w+)? not':  'didn\'t$1',
    'do( \\w+)? not':   'don\'t$1',
    'does( \\w+)? not': 'doesn\'t$1',
    'had( \\w+)? not':  'hadn\'t$1',
    'has( \\w+)? not':  'hasn\'t$1',
    'have( \\w+)? not': 'haven\'t$1',
    'is( \\w+)? not':   'isn\'t$1',
    'was( \\w+)? not':  'wasn\'t$1',
    'were( \\w+)? not': 'weren\'t$1',
    'will( \\w+)? not': 'won\'t$1',
  };

  static contractions_positive = {
    'I am':      'I\'m',
    'I had':     'I\'d',
    'I have':    'I\'ve',
    'I will':    'I\'ll',
    'he had':    'he\'d',
    'he has':    'he\'s',
    'he is':     'he\'s',
    'he will':   'he\'ll',
    'she had':   'she\'d',
    'she has':   'she\'s',
    'she is':    'she\'s',
    'she will':  'she\'ll',
    'it had':    'it\'d',
    'it has':    'it\'s',
    'it is':     'it\'s',
    'it will':   'it\'ll',
    'we are':    'we\'re',
    'we had':    'we\'d',
    'we have':   'we\'ve',
    'we will':   'we\'ll',
    'you are':   'you\'re',
    'you had':   'you\'d',
    'you have':  'you\'ve',
    'you will':  'you\'ll',
    'they are':  'they\'re',
    'they had':  'they\'d',
    'they have': 'they\'ve',
    'they will': 'they\'ll',
  };

  static subjects = [ 'I', 'you', 'he', 'she', 'it', 'we', 'you', 'they' ];

  static split(s) {
    return s.split(/\s+/);
  }

  static have_all_in(a, b) {
    return a.every((d) => b.includes(d));
  }

  static interpolate(sentence, verb, subject) {
    return (
      sentence
      .replaceAll('$s',  subject)
      .replaceAll('$v1', verb)
      .replaceAll('$vs', this.verbs[verb][0])
      .replaceAll('$vg', this.verbs[verb][1])
      .replaceAll('$v2', this.verbs[verb][2])
      .replaceAll('$v3', this.verbs[verb][3])
    );
  }

  static contraction(sentence) {
    let result = sentence;
    for(let form in this.contractions_negative) {
      result = result.replaceAll(new RegExp(form, 'g'), this.contractions_negative[form]);
    }
    if(result !== sentence) {
      return result;
    }
    for(let form in this.contractions_positive) {
      result = result.replaceAll(form, this.contractions_positive[form]);
    }
    if(result !== sentence) {
      return result;
    }
    return false;
  }

  static clean(sentence) {
    if(sentence !== false) {
      return sentence.replaceAll('#', '');
    }
    return false;
  }

  static sentences(verb, subject, attributes) {
    if(this.verbs[verb] === undefined) {
      return false;
    }
    let attributes_array = this.split(attributes);
    attributes_array.push(subject);
    for(let tense_attribute in this.tenses) {
      let tense_attribute_array = this.split(tense_attribute);
      if(this.have_all_in(attributes_array, tense_attribute_array)) {
        let sentence = this.interpolate(this.tenses[tense_attribute], verb, subject);
        return (
          {
            long: this.clean(sentence),
            short: this.clean(this.contraction(sentence))
          }
        );
      }
    }
    return false;
  }
};

export { Rules };
