#
# Codeforces submission CLI
#

CF_URL = 'https://codeforces.com'

gHeaders = {
  "user-agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.75 Safari/537.36",
  "accept-encoding": "gzip, deflate",
  "cookie": ""
}


def load_cookie():
  import subprocess
  command = "python misc/cookie_chrome.py codeforces.com --format=header"
  proc = subprocess.run(command.split(), check=True, capture_output=True)
  gHeaders['cookie'] = proc.stdout.strip()


def do_request(url, form_params=None):
  import urllib.request, urllib.parse, urllib.error, zlib
  data = urllib.parse.urlencode(form_params).encode() if form_params else None
  req = urllib.request.Request(url, headers=gHeaders, data=data)
  try:
    f = urllib.request.urlopen(req)
    resp = f.read()
    if f.headers.get('content-encoding') == 'gzip':
      resp = zlib.decompress(resp, 16 + zlib.MAX_WBITS)
    return resp.decode()
  except urllib.error.HTTPError as err:
    print(f":: REQUEST ERROR [{url}]")
    print(err.read().decode())
    raise err


def get_csrf():
  import re
  resp = do_request(CF_URL + '/problemset/submit')
  return dict(
    csrf_token = re.search('<input type=\'hidden\' name=\'csrf_token\' value=\'(.*?)\'/>', resp).group(1),
    ftaa = re.search('ftaa = "(.*?)"', resp).group(1),
    bfaa = re.search('bfaa = "(.*?)"', resp).group(1),
    _tta = '995') # NOTE: Not sure where this "_tta" comes from, but it seems always 995


def get_verdict():
  import re
  resp = do_request(CF_URL + '/problemset/status?my=on')
  tr = re.search('<tr data-submission-id(.*?)</tr>', resp, re.DOTALL).group(0)
  td_problem = re.search('<td class="status-small" data-problemId(.*?)</td>', tr, re.DOTALL).group(0)
  submission_id = re.search('data-submission-id="(.*?)"', tr).group(1)
  problem = re.search('<a href="(.*?)">(.*?)</a>', td_problem, re.DOTALL).group(2).strip()
  verdict_match = re.search('submissionVerdict="(.*?)"', tr)
  verdict = verdict_match.group(1) if verdict_match else '[NOT READY]'
  time = re.search('<td class="time-consumed-cell">(.*?)</td>', tr, re.DOTALL).group(1).strip().replace('&nbsp;', '')
  memory = re.search('<td class="memory-consumed-cell">(.*?)</td>', tr, re.DOTALL).group(1).strip().replace('&nbsp;', '')
  waiting = re.search('waiting="(.*?)"', tr).group(1) == 'true'
  return dict(id=submission_id, problem=problem, verdict=verdict, time=time, memory=memory, waiting=waiting)


def main(file, problem):
  print(':: Loading cookie...')
  load_cookie()

  print(':: Request to obtain CSRF...')
  form_params = get_csrf()

  print(':: Request to submit...')
  from datetime import datetime
  source = open(file).read().strip() + f"\n// submit.py [{datetime.isoformat(datetime.now())}]"
  form_params.update(
    source = source,
    submittedProblemCode = problem,
    programTypeId = '54', # GNU G++17 7.3.0
    action = 'submitSolutionFormSubmitted')
  do_request(CF_URL + '/problemset/submit', form_params)

  print(f":: Monitoring verdict... [{CF_URL + '/problemset/status?my=on'}]")
  import time
  while True:
    res = get_verdict()
    print(res)
    if not res['waiting']: break;
    time.sleep(1)


def main_cli():
  import sys, argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("file", type=str)
  parser.add_argument("--problem", type=str, required=True)
  sys.exit(main(**parser.parse_args().__dict__))


if __name__ == '__main__':
  main_cli()
